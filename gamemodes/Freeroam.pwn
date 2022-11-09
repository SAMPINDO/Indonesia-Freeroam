#pragma dynamic 		8388608
#define MAX_PLAYERS		50
#define MAX_VEHICLES	500
#define MAX_COMMANDS    128
#define YSI_NO_HEAP_MALLOC

#define SERVER_NAME			"Indonesia Freeroam"
#define SERVER_NAME_SHORT   "I:FR"
#define MODE_VERSION 		"2.0.5 Native!"

#if !defined BCRYPT_HASH_LENGTH
	#define BCRYPT_HASH_LENGTH 250
#endif

#if !defined BCRYPT_COST
	#define BCRYPT_COST 12
#endif

#define FOREACH_NO_LOCALS
#define YSI_NO_PLUGIN

#include <a_samp>
#include <sscanf2>
#include <samp_bcrypt>
#include <a_mysql>
//#include <crashdetect>

#include <YSI_Data\y_iterate>
#include <YSI_Coding\y_timers>
#include <YSI_Visual\y_commands>
#include <YSI_Server\y_colors>
#include <YSI_Coding\y_hooks>

#include <easyDialog>

#include "Extras/Macros"
#include "Extras/Teleports"
#include "Modules/Global"
#include "Modules/Player"
#include "Modules/PlayerVehicle"
#include "Modules/PlayerWorld"

// Default SA:MP Callbacks

main() { } // Don't ever use this shit!

public OnGameModeInit()
{
    print("--------------------------------------");
	print(SERVER_NAME);
	print("--------------------------------------");
	
	// MariaDB/MySQL Database
	
	Database = mysql_connect_file("mysql.ini");
    if(Database == MYSQL_INVALID_HANDLE)
    {
        print("[error] Failed to connect to database!");
        GameModeExit();
    }
	
	// SAMP Settings
	
	SetGameModeText(SERVER_NAME_SHORT" v"MODE_VERSION);
	AddPlayerClass(299,1956.2833,1342.9930,15.3746,270.1634,0,0,0,0,0,0);
    UsePlayerPedAnims();

	return 1;
}

public OnPlayerText(playerid, text[])
{
	if(ChatFlood[playerid] < 5)
	{
		ChatFlood[playerid]++;
		if(ChatFlood[playerid] == 5)
		{
			defer EnableChat(playerid);
		}
		return 1;
	}
	else SEM(playerid,"SERVER: Chat flood protection!");
 	return 0;
}

public OnGameModeExit()
{
	SavePlayers();
	mysql_close(Database);
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	return 1;
}

public OnPlayerConnect(playerid)
{
	forex(i,20)
	{
		SendClientMessage(playerid,X11_WHITE," ");
	}
	SendClientMessage(playerid, X11_LIGHTBLUE, "SERVER: "WHITE"Welcome to"CYAN" "SERVER_NAME);
	SendClientMessage(playerid, X11_LIGHTBLUE, "SERVER: "WHITE" use "YELLOW"/help "WHITE"to view all server commands!");
	SendDeathMessage(INVALID_PLAYER_ID,playerid,200);
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	SendDeathMessage(INVALID_PLAYER_ID,playerid,201);
    return 1;
}

public OnPlayerSpawn(playerid)
{
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid,9999999);
    return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
    return 1;
}

public OnPlayerUpdate(playerid)
{
	return 1;
}

public OnVehicleDamageStatusUpdate(vehicleid,playerid)
{
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    return 1;
}

// Commands

CMD:help(playerid,params[])
{
	SendClientMessage(playerid,X11_LIGHTBLUE,"**HELP** "WHITE"/help /weap /godmode /skin /killme /mycolor /jumpmode /jetpack /notele");
	SendClientMessage(playerid,X11_LIGHTBLUE,"**VEHICLE** "WHITE"/veh /mv /vehgodmode /vcolor /fix /boostmode /flip /lock /tow");
	SendClientMessage(playerid,X11_LIGHTBLUE,"**TELEPORT** "WHITE"/goto /gotols /gotosf /gotolv /drift[1-2] /tune[1-3]");
	SendClientMessage(playerid,X11_LIGHTBLUE,"**WORLD** "WHITE"/myworld /public /invite");
	return 1;
}
