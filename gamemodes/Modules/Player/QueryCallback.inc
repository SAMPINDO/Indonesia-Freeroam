function OnPlayerDataLoaded(playerid, race_check)
{
    if (race_check != g_MysqlRaceCheck[playerid]) return Kick(playerid);

	orm_setkey(PlayerData[playerid][ORM_ID], "id");

	new string[115];
	switch (orm_errno(PlayerData[playerid][ORM_ID]))
	{
		case ERROR_OK:
		{
			format(string, sizeof string, "This account (%s) is registered. Please login by entering your password in the field below:", Player[playerid][Name]);
			Dialog_Show(playerid,Player_Login,DIALOG_STYLE_PASSWORD,"Login to "SERVER_NAME_SHORT,WHITE"User: "YELLOW"%s\n"WHITE"Login Attempts: "YELLOW"%d / 5\n"WHITE"Password: "GREEN"(input below)","Login","Quit",playername,GetPVarInt(playerid,"LoginAttempt"));

			// from now on, the player has 30 seconds to login
			PlayerData[playerid][pLoginTimer] = SetTimerEx("OnLoginTimeout", 30, false, "d", playerid);
		}
		case ERROR_NO_DATA:
		{
			format(string, sizeof string, "Welcome %s, you can register by entering your password in the field below:", Player[playerid][Name]);
			ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "Registration", string, "Register", "Abort");
		}
	}
	return 1;
}

function OnLoginTimeout(playerid)
{
	// reset the variable that stores the timerid
	PlayerData[playerid][pLoginTimer] = 0;

	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Login", "You have been kicked for taking too long to login successfully to your account.", "Okay", "");
	DelayedKick(playerid);
	return 1;
}

function OnPlayerRegister(playerid)
{
	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Registration", "Account successfully registered, you have been automatically logged in.", "Okay", "");

	PlayerData[playerid][pIsLoggedIn] = true;

	SetSpawnInfo(playerid, NO_TEAM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
	return 1;
}

function OnPassswordHash(playerid)
{
	new dest[BCRYPT_HASH_LENGTH];
	bcrypt_get_hash(dest);
	CreatePlayerORM(playerid);
	GetPlayerName(playerid,PlayerInfo[playerid][pName],MAX_PLAYER_NAME);
	PlayerInfo[playerid][pPassword] = dest;
	PlayerInfo[playerid][pRegisterDate] = gettime();
	PlayerInfo[playerid][pLastLoginDate] = 0;
	PlayerInfo[playerid][Playtime] = 0;
	PlayerInfo[playerid][pSkin] = 299;
	PlayerInfo[playerid][pKills] = 0;
	PlayerInfo[playerid][pDeaths] = 0;
	orm_setkey(PlayerInfo[playerid][ORM_ID],"id");
	orm_save(PlayerInfo[playerid][ORM_ID]);
	return 1;
}

function OnPassswordCheck(playerid)
{
	new dest[BCRYPT_HASH_LENGTH];
	bcrypt_get_hash(dest);
	return !(strcmp(PlayerInfo[playerid][Password],dest,true));
}
