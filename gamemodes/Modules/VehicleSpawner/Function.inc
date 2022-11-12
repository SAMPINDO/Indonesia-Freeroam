stock SpawnVehicle(playerid, modelid)
{
    new Float:x, Float:y, Float:z, Float:a;
    if(IsPlayerInAnyVehicle(playerid))
    {
        GetVehiclePos(GetPlayerVehicleID(playerid), x, y, z);
        GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
    }
    else
    {
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, a);
    }
    if(PlayerData[playerid][pLastSpawnedVehicle] != INVALID_VEHICLE_ID)
    {
        DestroyVehicle(PlayerData[playerid][pLastSpawnedVehicle]); // Destroy the last spawned vehicle
    }
    PlayerData[playerid][pLastSpawnedVehicle] = CreateVehicle(modelid, x, y, z, a, 0, 0, 0);
    SetVehicleVirtualWorld(PlayerData[playerid][pLastSpawnedVehicle], GetPlayerVirtualWorld(playerid));
    LinkVehicleToInterior(PlayerData[playerid][pLastSpawnedVehicle], GetPlayerInterior(playerid));
    PutPlayerInVehicle(playerid, PlayerData[playerid][pLastSpawnedVehicle], 0);
    return 1;
}

/**
Airplanes
Boats
Bikes
Industrial
Lowriders
OffRoad
PublicService
RCVehicles
Saloons
SportsVehicles
Trailers
UniqueVehicles
 */

stock ShowVehicleTypeDialog(playerid)
{
    SendClientMessage(playerid, -1, "ShowVehicleTypeDialog called");
    inline Response(pid, dialogid, response, listitem, string:inputtext[])
    {
	    #pragma unused dialogid, inputtext, pid
        if(response)
        {
            switch(listitem)
            {
                case 0:
                    ShowModelSelectionMenu(playerid, Airplanes, "Airplanes");
                case 1:
                    ShowModelSelectionMenu(playerid, Boats, "Boats");
                case 2:
                    ShowModelSelectionMenu(playerid, Bikes, "Bikes");
                case 3:
                    ShowModelSelectionMenu(playerid, Industrial, "Industrial");
                case 4:
                    ShowModelSelectionMenu(playerid, Lowriders, "Lowriders");
                case 5:
                    ShowModelSelectionMenu(playerid, OffRoad, "OffRoad");
                case 6:
                    ShowModelSelectionMenu(playerid, PublicService, "Public Service");
                case 7:
                    ShowModelSelectionMenu(playerid, RCVehicles, "RC");
                case 8:
                    ShowModelSelectionMenu(playerid, Saloons, "Saloons");
                case 9:
                    ShowModelSelectionMenu(playerid, SportsVehicles, "Sports");
                case 10:
                    ShowModelSelectionMenu(playerid, Trailers, "Trailers");
                case 11:
                    ShowModelSelectionMenu(playerid, UniqueVehicles, "Unique");
            }
        }
    }
    Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_LIST, "Vehicle Type", "Airplanes\nBoats\nBikes\nIndustrial\nLowriders\nOffRoad\nPublic Service\nRC\nSaloons\nSports\nTrailers\nUnique", "Select", "Cancel");
    return 1;
}