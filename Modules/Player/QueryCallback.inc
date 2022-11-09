function Player_LoadData(playerid,check)
{
	if(check == RaceCheck[playerid])
	{
		new rows;
		cache_get_row_count(rows);
		if(rows == 1)
		{
			new ORM:ormid = CreatePlayerORM(playerid);
			orm_setkey(ormid,"id");
			orm_apply_cache(ormid,0);
			ShowLoginDialog(playerid);
		}
		else ShowRegisterDialog(playerid);
	}
	// if(check == RaceCheck[playerid])
	// {
	// 	new E_ORM_ERROR:errno = orm_errno(PlayerInfo[playerid][ORM_ID]);
	// 	if(errno == ERROR_OK)
	// 	{
	// 		orm_setkey(PlayerInfo[playerid][ORM_ID],"id");
	// 		ShowLoginDialog(playerid);
	// 	}
	// 	else if(errno == ERROR_NO_DATA)
	// 	{
	// 		orm_destroy(PlayerInfo[playerid][ORM_ID]);
	// 		ShowRegisterDialog(playerid);
	// 	}
	// 	else
	// 	{
	// 		orm_destroy(PlayerInfo[playerid][ORM_ID]);
	// 		SEM(playerid,"ERROR: An unexpected error has occurred, please try again later!");
	// 		Kick(playerid);
	// 	}
	// }
	// else
	// {
	// 	orm_destroy(PlayerInfo[playerid][ORM_ID]);
	// }
	return 1;
}
function Player_Register(playerid,check)
{
	if(check == RaceCheck[playerid])
	{
		if(orm_errno(PlayerInfo[playerid][ORM_ID]) == ERROR_OK)
		{
			SetSpawnInfo(playerid,-1,PlayerInfo[playerid][Skin],PlayerInfo[playerid][Pos][0],PlayerInfo[playerid][Pos][1],PlayerInfo[playerid][Pos][2],PlayerInfo[playerid][Pos][3],0,0,0,0,0,0);
			TogglePlayerSpectating(playerid,0);
			PlayerLogged[playerid] = true;
		}
		else
		{
			orm_destroy(PlayerInfo[playerid][ORM_ID]);
			SEM(playerid,"ERROR: An unexpected error has occurred, please try again later!");
			Kick(playerid);
		}
	}
	else
	{
		orm_destroy(PlayerInfo[playerid][ORM_ID]);
	}
	return 1;
}


function OnPassswordCheck(playerid)
{
	new dest[BCRYPT_HASH_LENGTH];
	bcrypt_get_hash(dest);
	return !(strcmp(PlayerInfo[playerid][Password],dest,true));
}

function OnPassswordHash(playerid)
{
	new dest[BCRYPT_HASH_LENGTH];
	bcrypt_get_hash(dest);
	CreatePlayerORM(playerid);
	GetPlayerName(playerid,PlayerInfo[playerid][Name],MAX_PLAYER_NAME);
	PlayerInfo[playerid][Password] = dest;
	PlayerInfo[playerid][RegisterDate] = gettime();
	PlayerInfo[playerid][LastLoginDate] = 0;
	PlayerInfo[playerid][Playtime] = 0;
	PlayerInfo[playerid][Skin] = 299;
	PlayerInfo[playerid][Pos][0] = 1956.2833;
	PlayerInfo[playerid][Pos][1] = 1342.9930;
	PlayerInfo[playerid][Pos][2] = 15.3746;
	PlayerInfo[playerid][Pos][3] = 270.1634;
	PlayerInfo[playerid][Kills] = 0;
	PlayerInfo[playerid][Deaths] = 0;
	orm_setkey(PlayerInfo[playerid][ORM_ID],"id");
	orm_insert(PlayerInfo[playerid][ORM_ID],"Player_Register","dd",playerid,RaceCheck[playerid]);
	return 1;
}