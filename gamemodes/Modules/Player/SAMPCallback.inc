#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_va>
#include <YSI_Core\y_debug>
#include <YSI_Extra\y_inline_mysql>
#include <YSI_Extra\y_inline_timers>



static void:Player_PromptCredential(playerid)
{
    if (Player_IsRegistered(playerid))
    {
        SendClientMessage(playerid, X11_WHITE, "This username is registered. Please use "LAWN_GREEN"/login "WHITE"to verify your ownership.");
        SendClientMessage(playerid, X11_WHITE, "In case you are need a new username, please reconnect with your new username for now.");
        // SendClientMessage(playerid, X11_WHITE, "In case you are need a new username, please use "LAWN_GREEN"/guest"WHITE" to change your current username.");
    }
    else
    {
        SendClientMessage(playerid, X11_WHITE, "This username is not registered. Please use "LAWN_GREEN"/register"WHITE" to create a new one and save your game progress.");
    }
}

static void:Player_CheckUsername(playerid)
{
    inline const CheckUsername()
    {
        if (cache_num_rows() == 0)
        {
            Player_ResetData(playerid);
            Player_InitORM(playerid);
            Player_InitGuestAccount(playerid);
        }
        else
        {
            Player_ResetData(playerid);
            Player_InitORM(playerid);

            cache_get_value_name_int(0, "id", PlayerData[playerid][ID]);
            Player_LoadAccount(playerid);
        }

        Player_PromptCredential(playerid);
        Player_StartLoginTimeoutTimer(playerid);
        SendClientMessage(playerid, X11_WHITE, "You will be kicked from server in "LAWN_GREEN"60 seconds"WHITE" if you are not spawning.");
    }

    if (!Player_IsDataLocked(playerid))
    {
        new
            string:name[MAX_PLAYER_NAME + 1]
        ;

        GetPlayerName(playerid, name, sizeof(name));
        MySQL_TQueryInline(g_Database, using inline CheckUsername, "\
        SELECT \
            `id` \
        FROM \
            `"ACCOUNTS_TABLE_NAME"` \
        WHERE \
            `username` = \"%e\";\
        ", name);
    }
}



#include <YSI_Coding\y_hooks>
hook OnScriptInit()
{
    // Database
    PlayerData[MAX_PLAYERS][ORM_ID] = MYSQL_INVALID_ORM;
    PlayerData[MAX_PLAYERS][ID] = 0;
    format(PlayerData[MAX_PLAYERS][Username], MAX_PLAYER_NAME + 1, "");
    format(PlayerData[MAX_PLAYERS][Password], BCRYPT_HASH_LENGTH, "");
    format(PlayerData[MAX_PLAYERS][Email], EMAIL_ADDRESS_LENGTH, "");
    format(PlayerData[MAX_PLAYERS][DiscordID], DISCORD_ID_LENGTH, "");
    PlayerData[MAX_PLAYERS][DiscordBoundAt] = 0;
    PlayerData[MAX_PLAYERS][AdminLevel] = 0;
    PlayerData[MAX_PLAYERS][Money] = 0;
    PlayerData[MAX_PLAYERS][Bank] = 0;
    PlayerData[MAX_PLAYERS][Level] = 0;
    PlayerData[MAX_PLAYERS][EXP] = 0;
    PlayerData[MAX_PLAYERS][Kills] = 0;
    PlayerData[MAX_PLAYERS][Deaths] = 0;
    PlayerData[MAX_PLAYERS][ModelSkinID] = 0;
    PlayerData[MAX_PLAYERS][PlayTime] = 0;
    PlayerData[MAX_PLAYERS][VIPLevel] = 0;
    PlayerData[MAX_PLAYERS][VIPExpiredAt] = 0;
    PlayerData[MAX_PLAYERS][RegisteredAt] = 0;
    PlayerData[MAX_PLAYERS][CreatedAt] = 0;
    PlayerData[MAX_PLAYERS][UpdatedAt] = 0;

    // In-game
    PlayerData[MAX_PLAYERS][IsLoggedIn] = false;
    PlayerData[MAX_PLAYERS][PlayTimeStart] = 0;
    PlayerData[MAX_PLAYERS][LoginAttempt] = 0;
    return 1;
}

#include <YSI_Coding\y_hooks>
hook OnPlayerConnect(playerid)
{
    PLAYER_IS_NOT_NPC(playerid, 1);

    PLAYER_MUST_CONNECTED(playerid, 1);

    new
        count = 1
    ;

    inline CheckLock()
    {
        PLAYER_MUST_CONNECTED(playerid, 1);

        if (Player_IsDataLocked(playerid))
        {
            new
                string:text[30]
            ;

            format(text, sizeof(text), "~w~Please wait... (~r~%d~w~)", count);
            GameTextForPlayer(playerid, text, 1500, 3);

            count++;
            Timer_CreateCallback(using inline CheckLock, 1_000, 1);
            return 1;
        }

        Player_CheckUsername(playerid);
        return 1;
    }

    Timer_CreateCallback(using inline CheckLock, 1_000, 1);
    return 1;
}

#include <YSI_Coding\y_hooks>
hook OnPlayerAttemptLogin(playerid, number_of_attempt)
{
    PLAYER_IS_NOT_NPC(playerid, 1);

    PLAYER_MUST_CONNECTED(playerid, 1);

    va_SendClientMessage(playerid, X11_WHITE, "Invalid password. ("TOMATO"%d"WHITE"/"TOMATO"%d"WHITE")", PlayerData[playerid][LoginAttempt], MAXIMUM_LOGIN_FAILED);

    if (Player_HasMaximumLoginAttempt(playerid))
    {
        SendClientMessage(playerid, X11_TOMATO, "You were kicked because of maximum attempt login.");
        defer Player_KickDelayed(playerid);
        return 1;
    }

    Player_ShowLoginDialog(playerid);
    return 1;
}

#include <YSI_Coding\y_hooks>
hook OnPlayerLoginSuccess(playerid)
{
    PLAYER_IS_NOT_NPC(playerid, 1);

    PLAYER_MUST_CONNECTED(playerid, 1);

    Player_StopLoginTimeout(playerid);
    Player_MarkStartPlayTime(playerid);
    va_SendClientMessage(playerid, X11_WHITE, "You are logged in. Welcome back, "LAWN_GREEN"%s"WHITE"!", PlayerData[playerid][Username]);
    return 1;
}

#include <YSI_Coding\y_hooks>
hook OnPlayerRegisterSuccess(playerid)
{
    PLAYER_IS_NOT_NPC(playerid, 1);

    PLAYER_MUST_CONNECTED(playerid, 1);

    va_SendClientMessage(playerid, X11_WHITE, "Register success. Please insert password to log in.");

    Player_ShowLoginDialog(playerid);
    return 1;
}

#include <YSI_Coding\y_hooks>
hook OnPlayerSaveSuccess(playerid)
{
    // P:1(va_return("Player ID data (playerid=%d) saved successfully.", playerid));
    return 1;
}

#include <YSI_Coding\y_hooks>
hook OnPlayerRequestSpawn(playerid)
{
    if (!Player_IsLoggedIn(playerid))
    {
        SendClientMessage(playerid, X11_TOMATO, "You are not logged in. Please log in first before click \"Spawn\".");
        return 0;
    }

    return 1;
}

#include <YSI_Coding\y_hooks>
hook OnPlayerDisconnect(playerid, reason)
{
    #pragma unused reason

    if (!Player_IsLoggedIn(playerid))
        return Player_ReleaseLock(playerid);

    Player_StopLoginTimeout(playerid);
    Player_UpdatePlayTime(playerid);
    Player_SaveData(playerid, true);
    return 1;
}
