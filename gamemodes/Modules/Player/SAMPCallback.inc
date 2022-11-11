hook OnPlayerConnect(playerid)
{
    g_MysqlRaceCheck[playerid]++;

	// reset player data
	static const empty_player[E_PLAYERS];
	PlayerData[playerid] = empty_player;

	GetPlayerName(playerid, PlayerData[playerid][pName], MAX_PLAYER_NAME);

    PlayerData[playerid][ORM_ID] = CreateORM(playerid);

    // tell the orm system to load all data, assign it to our variables and call our callback when ready
	orm_load(PlayerData[playerid][ORM_ID], "OnPlayerDataLoaded", "dd", playerid, g_MysqlRaceCheck[playerid]);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    g_MysqlRaceCheck[playerid]++;

	UpdatePlayerData(playerid);

	// if the player was kicked before the time expires (30 seconds), kill the timer
	if (PlayerData[playerid][pLoginTimer])
	{
		KillTimer(PlayerData[playerid][pLoginTimer]);
		PlayerData[playerid][pLoginTimer] = 0;
	}

	// sets "IsLoggedIn" to false when the player disconnects, it prevents from saving the player data twice when "gmx" is used
	PlayerData[playerid][pIsLoggedIn] = false;

    return 1;
}
