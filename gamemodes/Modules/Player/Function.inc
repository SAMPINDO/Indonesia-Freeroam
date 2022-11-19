#include <a_mysql>

#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_va>
#include <YSI_Core\y_debug>
#include <YSI_Extra\y_inline_bcrypt>
#include <YSI_Extra\y_inline_mysql>
#include <YSI_Visual\y_dialog>



bool:Player_IsLoggedIn(playerid)
{
    PLAYER_ID_MUST_VALID(playerid, false);

    return (PlayerData[playerid][IsLoggedIn]);
}

Player_ResetData(playerid)
{
    PLAYER_ID_MUST_VALID(playerid, 0);

    PlayerData[playerid] = PlayerData[MAX_PLAYERS];
    return 1;
}

bool:Player_HasMaximumLoginAttempt(playerid)
{
    return (PlayerData[playerid][LoginAttempt] > MAXIMUM_LOGIN_FAILED);
}

Player_InitORM(playerid)
{
    PLAYER_ID_MUST_VALID(playerid, 0);

    new
        ORM:orm = orm_create(ACCOUNTS_TABLE_NAME, g_Database)
    ;

    PlayerData[playerid][ORM_ID] = orm;
    orm_addvar_int(orm, PlayerData[playerid][ID], "id");
    orm_addvar_string(orm, PlayerData[playerid][Username], MAX_PLAYER_NAME + 1, "username");
    orm_addvar_string(orm, PlayerData[playerid][Password], BCRYPT_HASH_LENGTH, "password");
    orm_addvar_string(orm, PlayerData[playerid][Email], EMAIL_ADDRESS_LENGTH, "email");
    orm_addvar_string(orm, PlayerData[playerid][DiscordID], DISCORD_ID_LENGTH, "discord_id");
    orm_addvar_int(orm, PlayerData[playerid][DiscordBoundAt], "discord_bound_at");
    orm_addvar_int(orm, PlayerData[playerid][AdminLevel], "admin_level");
    orm_addvar_int(orm, PlayerData[playerid][Money], "money");
    orm_addvar_int(orm, PlayerData[playerid][Bank], "bank");
    orm_addvar_int(orm, PlayerData[playerid][Level], "level");
    orm_addvar_int(orm, PlayerData[playerid][EXP], "exp");
    orm_addvar_int(orm, PlayerData[playerid][Kills], "kills");
    orm_addvar_int(orm, PlayerData[playerid][Deaths], "deaths");
    orm_addvar_int(orm, PlayerData[playerid][ModelSkinID], "model_skin_id");
    orm_addvar_int(orm, PlayerData[playerid][PlayTime], "play_time");
    orm_addvar_int(orm, PlayerData[playerid][VIPLevel], "vip_level");
    orm_addvar_int(orm, PlayerData[playerid][VIPExpiredAt], "vip_expired_at");
    orm_addvar_int(orm, PlayerData[playerid][RegisteredAt], "registered_at");
    orm_addvar_int(orm, PlayerData[playerid][CreatedAt], "created_at");
    orm_addvar_int(orm, PlayerData[playerid][UpdatedAt], "updated_at");

    orm_setkey(orm, "id");
    return 1;
}

void:Player_StartLoginTimeoutTimer(playerid)
{
    if (Timer_IsRunning(PlayerData[playerid][LoginTimer]))
        stop PlayerData[playerid][LoginTimer];

    PlayerData[playerid][LoginTimer] = defer Player_KickLoginTimeout(playerid);
    return 1;
}

Player_ReleaseLock(playerid)
{
    if (playerid < 0 || playerid >= MAX_PLAYERS)
        return 0;

    orm_destroy(PlayerData[playerid][ORM_ID]);
    PlayerData[playerid][ORM_ID] = MYSQL_INVALID_ORM;
    return 1;
}

bool:Player_IsDataLocked(playerid)
{
    PLAYER_ID_MUST_VALID(playerid, false);

    return (PlayerData[playerid][ORM_ID] != MYSQL_INVALID_ORM);
}

bool:Player_IsRegistered(playerid)
{
    PLAYER_MUST_CONNECTED(playerid, false);

    return (!!PlayerData[playerid][ID]);
}

Player_InitGuestAccount(playerid)
{
    PLAYER_ID_MUST_VALID(playerid, 0);

    PlayerData[playerid][ID] = 0;
    GetPlayerName(playerid, PlayerData[playerid][Username], MAX_PLAYER_NAME);

    return 1;
}

Player_LoadAccount(playerid)
{
    PLAYER_ID_MUST_VALID(playerid, 0);

    orm_load(PlayerData[playerid][ORM_ID]);
    return 1;
}

Player_SaveData(playerid, bool:release_lock = false)
{
    PLAYER_IS_NOT_NPC(playerid, 0);

    PLAYER_MUST_CONNECTED(playerid, 0);

    if (PlayerData[playerid][ORM_ID] == MYSQL_INVALID_ORM)
        return 0;

    inline OnAfterSave()
    {
        if (release_lock)
        {
        Player_ReleaseLock(playerid);
        }

        CallRemoteFunction("OnPlayerSaveAccountSuccess", "d", playerid);
        return 1;
    }

    PlayerData[playerid][Money] = GetPlayerMoney(playerid);

    ORM_SaveInline(PlayerData[playerid][ORM_ID], using inline OnAfterSave);
    return 1;
}

Player_ShowLoginDialog(playerid)
{
    PLAYER_MUST_CONNECTED(playerid, 0);

    if (Player_IsLoggedIn(playerid))
        return 0;

    inline const ResponseLoginDialog(pid, dialogid, response, listitem, string:inputtext[])
    {
        #pragma unused pid, dialogid, listitem, inputtext

        if (!response)
        {
        return 1;
        }

        inline const CheckPassword(success)
        {
        if (!success)
        {
            PlayerData[playerid][LoginAttempt]++;
            CallRemoteFunction("OnPlayerAttemptLogin", "dd", playerid, PlayerData[playerid][LoginAttempt]);
            return 1;
        }

        PlayerData[playerid][LoginAttempt] = 0;
        PlayerData[playerid][IsLoggedIn] = true;

        CallRemoteFunction("OnPlayerLoginSuccess", "d", playerid);
        return 1;
        }

        BCrypt_CheckInline(inputtext, PlayerData[playerid][Password], using inline CheckPassword);
        return 1;
    }

    Dialog_ShowCallback(playerid, using inline ResponseLoginDialog, DIALOG_STYLE_PASSWORD, "Login", "Please insert your password.", "Submit", "Cancel");
    return 1;
}

Player_ShowRegisterDialog(playerid)
{
    PLAYER_MUST_CONNECTED(playerid, 0);

    if (Player_IsLoggedIn(playerid))
        return 0;

    inline const ResponseRegisterDialog(pid, dialogid, response, listitem, string:inputtext[])
    {
        #pragma unused pid, dialogid, listitem, inputtext

        if (!response)
        {
        return 1;
        }

        inline const ReceiveHashedPassword(string:hashed[])
        {
        format(PlayerData[playerid][Password], BCRYPT_HASH_LENGTH, "%s", hashed);

        inline const InsertAccountSuccess()
        {
            PlayerData[playerid][ID] = cache_insert_id();
            CallRemoteFunction("OnPlayerRegisterSuccess", "d", playerid);
        }

        ORM_SaveInline(PlayerData[playerid][ORM_ID], using inline InsertAccountSuccess);
        return 1;
        }

        BCrypt_HashInline(inputtext, BCRYPT_COST, using inline ReceiveHashedPassword);
        return 1;
    }

    Dialog_ShowCallback(
        playerid,
        using inline ResponseRegisterDialog,
        DIALOG_STYLE_PASSWORD,
        "Register",
        va_return(""WHITE"Username: "LAWN_GREEN"%s"WHITE"\nPlease insert your password.", PlayerData[playerid][Username]),
        "Submit",
        "Cancel"
    );
    return 1;
}

// Player_ChangeUsername(playerid, const string:new_name[])
// {
//   PLAYER_MUST_CONNECTED(playerid, 0);

//   if (Player_IsLoggedIn(playerid))
// 		return 0;

//   if (strlen(new_name) < 3 || strlen(new_name) > MAX_PLAYER_NAME)
//     return 0;

//   return SetPlayerName(playerid, new_name);
// }

Player_MarkStartPlayTime(playerid)
{
    PLAYER_ID_MUST_VALID(playerid, 0);

    PlayerData[playerid][PlayTimeStart] = gettime();
    return 1;
}

Player_UpdatePlayTime(playerid)
{
    PLAYER_ID_MUST_VALID(playerid, 0);

    PlayerData[playerid][PlayTime] += (gettime() - PlayerData[playerid][PlayTimeStart]);
    return 1;
}

void:Player_StopLoginTimeout(playerid)
{
    stop PlayerData[playerid][LoginTimer];
}

void:Player_SaveAll()
{
    foreach(new playerid : Player)
    {
        Player_SaveData(playerid);
    }
}
