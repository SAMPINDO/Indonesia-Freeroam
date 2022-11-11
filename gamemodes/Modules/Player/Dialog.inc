Dialog:Player_Login(playerid,response,listitem,inputtext[])
{
	if(response)
	{
		if(LoginPlayer(playerid,inputtext))
		{
			SetSpawnInfo(playerid,-1,0,0,0,0,0,0,0,0,0,0,0);
			TogglePlayerSpectating(playerid,0);
			PlayerData[playerid][pLastLoginDate] = gettime();
			PlayerData[playerid][pIsLoggedIn] = true;
		}
		else
		{
			new attempts = GetPVarInt(playerid,"LoginAttempt");
			if(attempts < 4)
			{
				SetPVarInt(playerid,"LoginAttempt",(attempts+1));
			}
			else Kick(playerid);
		}
	}
	return 1;
}
Dialog:Player_Register(playerid,response,listitem,inputtext[])
{
	if(response)
	{
		if(RegisterPlayer(playerid,inputtext) == 0) ShowRegisterDialog(playerid);
	}
	return 1;
}