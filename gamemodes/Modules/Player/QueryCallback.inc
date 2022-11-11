function OnPlayerDataLoaded(playerid, race_check)
{
    if (race_check != g_MysqlRaceCheck[playerid]) return Kick(playerid);

	orm_setkey(PlayerData[playerid][ORM_ID], "id");

	new string[115];
	switch (orm_errno(PlayerData[playerid][ORM_ID]))
	{
		case ERROR_OK:
		{
			format(string, sizeof string, "This account (%s) is registered. Please login by entering your password in the field below:", PlayerData[playerid][pName]);
			Dialog_Show(playerid,Player_Login,DIALOG_STYLE_PASSWORD,"Login to "SERVER_NAME_SHORT,WHITE"User: "YELLOW"%s\n"WHITE"Login Attempts: "YELLOW"%d / 5\n"WHITE"Password: "GREEN"(input below)","Login","Quit",PlayerData[playerid][pName],GetPVarInt(playerid,"LoginAttempt"));

			// from now on, the player has 30 seconds to login
			PlayerData[playerid][pLoginTimer] = SetTimerEx("OnLoginTimeout", 30, false, "d", playerid);
		}
		case ERROR_NO_DATA:
		{
			format(string, sizeof string, "Welcome %s, you can register by entering your password in the field below:", PlayerData[playerid][pName]);
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

	SetSpawnInfo(playerid, NO_TEAM, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
	return 1;
}

function OnPassswordHash(playerid)
{
	new dest[BCRYPT_HASH_LENGTH];
	bcrypt_get_hash(dest);
	GetPlayerName(playerid,PlayerData[playerid][pName],MAX_PLAYER_NAME);
	format(PlayerData[playerid][pPassword], BCRYPT_HASH_LENGTH, "%s", dest);
	PlayerData[playerid][pRegisterDate] = gettime();
	PlayerData[playerid][pLastLoginDate] = 0;
	PlayerData[playerid][pPlaytime] = 0;
	PlayerData[playerid][pSkin] = 299;
	PlayerData[playerid][pKills] = 0;
	PlayerData[playerid][pDeaths] = 0;
	orm_setkey(PlayerData[playerid][ORM_ID],"id");
	orm_save(PlayerData[playerid][ORM_ID]);
	return 1;
}

function OnPassswordCheck(playerid)
{
	new dest[BCRYPT_HASH_LENGTH];
	bcrypt_get_hash(dest);
	return !(strcmp(PlayerData[playerid][pPassword],dest,true));
}
