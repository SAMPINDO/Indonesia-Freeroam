enum E_PLAYERS
{
	ORM: ORM_ID,

	pID,
	pName[MAX_PLAYER_NAME],
	pPassword[250], // Password is bcrypt hash with 250 Max
	pKills,
	pDeaths,

	bool: pIsLoggedIn,
	pLoginAttempts,
	pLoginTimer
};
new PlayerData[MAX_PLAYERS][E_PLAYERS];

new g_MysqlRaceCheck[MAX_PLAYERS];