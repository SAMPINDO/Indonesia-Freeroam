stock ORM:CreatePlayerORM(playerid)
{
	new ORM:ormid = PlayerInfo[playerid][ORM_ID] = orm_create("players",Database);
	orm_addvar_int(ormid,PlayerInfo[playerid][ID],"id");
	orm_addvar_string(ormid,PlayerInfo[playerid][Name],32,"name");
	orm_addvar_string(ormid,PlayerInfo[playerid][Password],130,"password");
	orm_addvar_int(ormid,PlayerInfo[playerid][RegisterDate],"register_date");
	orm_addvar_int(ormid,PlayerInfo[playerid][LastLoginDate],"last_login_date");
	orm_addvar_int(ormid,PlayerInfo[playerid][Playtime],"playtime");
	orm_addvar_int(ormid,PlayerInfo[playerid][Skin],"skin");
	orm_addvar_float(ormid,PlayerInfo[playerid][Pos][0],"pos_x");
	orm_addvar_float(ormid,PlayerInfo[playerid][Pos][1],"pos_y");
	orm_addvar_float(ormid,PlayerInfo[playerid][Pos][2],"pos_z");
	orm_addvar_float(ormid,PlayerInfo[playerid][Pos][3],"pos_a");
	orm_addvar_int(ormid,PlayerInfo[playerid][Kills],"kills");
	orm_addvar_int(ormid,PlayerInfo[playerid][Deaths],"deaths");
	return ormid;
}
stock LoadPlayer(playerid)
{
	new playername[MAX_PLAYER_NAME],string[128];
	GetPlayerName(playerid,playername,sizeof(playername));
	mysql_format(Database,string,sizeof(string),"SELECT * FROM `players` WHERE `name`='%e'",playername);
	mysql_pquery(Database,string,"Player_LoadData","dd",playerid,RaceCheck[playerid]);
	// new ORM:ormid = CreatePlayerORM(playerid);
	// GetPlayerName(playerid,PlayerInfo[playerid][Name],MAX_PLAYER_NAME);
	// orm_setkey(ormid,"name");
	// orm_select(ormid,"Player_LoadData","dd",playerid,RaceCheck[playerid]);
	return 1;
}
stock ShowLoginDialog(playerid)
{
	new playername[MAX_PLAYER_NAME];
	GetPlayerName(playerid,playername,sizeof(playername));
	Dialog_Show(playerid,Player_Login,DIALOG_STYLE_PASSWORD,"Login to "SERVER_NAME_SHORT,WHITE"User: "YELLOW"%s\n"WHITE"Login Attempts: "YELLOW"%d / 5\n"WHITE"Password: "GREEN"(input below)","Login","Quit",playername,GetPVarInt(playerid,"LoginAttempt"));
	return 1;
}
stock ShowRegisterDialog(playerid)
{
	new playername[MAX_PLAYER_NAME];
	GetPlayerName(playerid,playername,sizeof(playername));
	Dialog_Show(playerid,Player_Register,DIALOG_STYLE_PASSWORD,"Register to "SERVER_NAME_SHORT,CYAN"Your account is not registered!\n"WHITE"User: "YELLOW"%s\n"WHITE"Password: "GREEN"(input below)","Login","Quit",playername);
	return 1;
}
stock bool:LoginPlayer(playerid,const password[])
{
	if(IsNull(password)) 
		return false;

	bcrypt_hash(playerid,"OnPassswordCheck",password,BCRYPT_COST);
	return true;
}

stock RegisterPlayer(playerid,const password[])
{
	if(IsNull(password)) return 0;
	bcrypt_hash(playerid,"OnPassswordHash",password,BCRYPT_COST);
	return 1;
}
stock bool:IsPlayerLoggedIn(playerid)
{
	return (IsPlayerConnected(playerid) && PlayerLogged[playerid]);
}
stock SavePlayer(playerid)
{
	GetPlayerPos(playerid,PlayerInfo[playerid][Pos][0],PlayerInfo[playerid][Pos][1],PlayerInfo[playerid][Pos][2]);
	GetPlayerFacingAngle(playerid,PlayerInfo[playerid][Pos][3]);
	PlayerInfo[playerid][Skin] = GetPlayerSkin(playerid);
	orm_update(PlayerInfo[playerid][ORM_ID]);
	return 1;
}
stock SavePlayers()
{
	foreach(new playerid : Player)
	{
		if(PlayerLogged[playerid]) SavePlayer(playerid);
	}
	return 1;
}
