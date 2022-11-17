#pragma dynamic 		8388608 // 8MB


#define SERVER_NAME			"Indonesia Freeroam"
#define SERVER_NAME_SHORT   "I:FR"
#define MODE_VERSION 		"I:FR 0.0.1 Initialization"

#include <a_samp>
#include <sscanf2>
#include <samp_bcrypt>
#include <a_mysql>

#include <YSI_Data\y_iterate>
#include <YSI_Coding\y_timers>
#include <YSI_Visual\y_commands>
#include <YSI_Server\y_colors>
#include <YSI_Coding\y_va>
#include <YSI_Visual\y_dialog>
// Include for `inline`.
#include <YSI_Coding\y_inline>

#include <scg>
#include <easyDialog>
#include <mSelection>

#include "Utils/Macro"

#include "Modules/Wrapper"

main() { Command_SetDeniedReturn(true); } // Pake gamemodeinit aja

public OnGameModeInit() 
{
	print("--------------------------------------");
	print(""SERVER_NAME" #KitaPeduliDenganWahyu");
	print("--------------------------------------");
	SetGameModeText(MODE_VERSION);
	
	#if DEBUG_MODE then
		mysql_log(ALL);
	#endif
	g_Database = mysql_connect_file("mysql.ini");

	if(g_Database == MYSQL_INVALID_HANDLE)
	{
		print("[error] Failed to connect to database!");
		SendRconCommand("exit");
		return 1;
	}

	ShowNameTags(1);
	UsePlayerPedAnims();
	DisableInteriorEnterExits();
	SetNameTagDrawDistance(40.0);
	EnableStuntBonusForAll(false);

	AddPlayerClass(299,1956.2833,1342.9930,15.3746,270.1634,0,0,0,0,0,0);
	return 1;
}

public OnPlayerText(playerid, text[])
{
	return 1;
}

public OnGameModeExit()
{
	if(g_Database != MYSQL_INVALID_HANDLE)
	{
		Player_SaveAll(); // Save Player Data When Database Is Connected and Server Is Shutting Down
	}
	mysql_close(g_Database);
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

public e_COMMAND_ERRORS:OnPlayerCommandReceived(playerid, cmdtext[], e_COMMAND_ERRORS:success) 
{
    if (success == COMMAND_UNDEFINED) 
    {
        new 
            guessCmd[32], 
            dist = Command_Guess(guessCmd, cmdtext);
  
        if (dist < 3)
        {
            SendClientMessageEx(playerid, -1, "{B9C9BF}SERVER: "WHITE"\"%s\"{B9C9BF} tidak di temukan!, apakah \"%s\"?", cmdtext, guessCmd);
        }
        else
        {
            SendClientMessageEx(playerid, -1, "{B9C9BF}SERVER: "WHITE"\"%s\"{B9C9BF} tidak di temukan!", cmdtext);
        }
        return COMMAND_DENIED;
    }
    return COMMAND_OK;
}

// Commands

YCMD:help(playerid,params[],help)
{
	SendClientMessage(playerid,X11_LIGHTBLUE,"**HELP** "WHITE"/help /weap /godmode /skin /killme /mycolor /jumpmode /jetpack /notele");
	SendClientMessage(playerid,X11_LIGHTBLUE,"**VEHICLE** "WHITE"/veh /mv /vehgodmode /vcolor /fix /boostmode /flip /lock /tow");
	SendClientMessage(playerid,X11_LIGHTBLUE,"**TELEPORT** "WHITE"/goto /gotols /gotosf /gotolv /drift[1-2] /tune[1-3]");
	SendClientMessage(playerid,X11_LIGHTBLUE,"**WORLD** "WHITE"/myworld /public /invite");
	return 1;
}