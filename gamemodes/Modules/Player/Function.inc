stock ORM:CreateORM(playerid)
{
    new ORM: ormid = orm_create("players", g_Database);
    orm_addvar_int(ormid, Player[playerid][pID], "id");
	orm_addvar_string(ormid, Player[playerid][pName], MAX_PLAYER_NAME, "username");
	orm_addvar_string(ormid, Player[playerid][pPassword], 65, "password");
	orm_addvar_string(ormid, Player[playerid][pSalt], 17, "salt");
	orm_addvar_int(ormid, Player[playerid][pKills], "kills");
	orm_addvar_int(ormid, Player[playerid][pDeaths], "deaths");

	orm_setkey(ormid, "username");
    return ormid;
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

DelayedKick(playerid, time = 500)
{
	SetTimerEx("_KickPlayerDelayed", time, false, "d", playerid);
	return 1;
}
function _KickPlayerDelayed(playerid)
{
    Kick(playerid);
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
