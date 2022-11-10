hook OnPlayerConnect(playerid)
{
    g_MysqlRaceCheck[playerid]++;

	// reset player data
	static const empty_player[E_PLAYERS];
	PlayerData[playerid] = empty_player;

	GetPlayerName(playerid, PlayerData[playerid][Name], MAX_PLAYER_NAME);

    PlayerData[playerid][ORM_ID] = CreateORM(playerid);

    // tell the orm system to load all data, assign it to our variables and call our callback when ready
	orm_load(ormid, "OnPlayerDataLoaded", "dd", playerid, g_MysqlRaceCheck[playerid]);
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    g_MysqlRaceCheck[playerid]++;

	UpdatePlayerData(playerid, reason);

	// if the player was kicked before the time expires (30 seconds), kill the timer
	if (PlayerData[playerid][LoginTimer])
	{
		KillTimer(PlayerData[playerid][LoginTimer]);
		PlayerData[playerid][LoginTimer] = 0;
	}

	// sets "IsLoggedIn" to false when the player disconnects, it prevents from saving the player data twice when "gmx" is used
	Player[playerid][IsLoggedIn] = false;

    return Y_HOOKS_CONTINUE_RETURN_1;
}
