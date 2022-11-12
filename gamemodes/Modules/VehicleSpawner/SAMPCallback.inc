#include <YSI_Coding\y_hooks> // Always Create new HOOKING!
hook OnGameModeInit()
{
    Boats = LoadModelSelectionMenu("vehicles/Boat.txt");
    Bikes = LoadModelSelectionMenu("vehicles/Bike.txt");
    OffRoad = LoadModelSelectionMenu("vehicles/OffRoad.txt");
    Saloons = LoadModelSelectionMenu("vehicles/Saloon.txt");
    Trailers = LoadModelSelectionMenu("vehicles/Trailer.txt");
    Lowriders = LoadModelSelectionMenu("vehicles/Lowrider.txt");
    Helicopters = LoadModelSelectionMenu("vehicles/Helicopter.txt");
    Airplanes = LoadModelSelectionMenu("vehicles/Airplane.txt");
    Industrial = LoadModelSelectionMenu("vehicles/Industrial.txt");
    RCVehicles = LoadModelSelectionMenu("vehicles/RC.txt");
    Helicopters = LoadModelSelectionMenu("vehicles/Helicopter.txt");
    PublicService = LoadModelSelectionMenu("vehicles/PublicService.txt");
    SportsVehicles = LoadModelSelectionMenu("vehicles/Sport.txt");
    UniqueVehicles = LoadModelSelectionMenu("vehicles/Unique.txt");

    return 1;
}

#include <YSI_Coding\y_hooks> // Always Create new HOOKING!
hook OnPlayerModelSelection(playerid, response, listid, modelid)
{
    if(listid == Boats || listid == Bikes || listid == OffRoad || listid == Saloons || listid == Trailers || listid == Lowriders || listid == Helicopters || listid == Airplanes || listid == Industrial || listid == RCVehicles || listid == Helicopters || listid == PublicService || listid == SportsVehicles || listid == UniqueVehicles)
        if(response)
            SpawnVehicle(playerid, modelid);
    
    return 1;
}

#include <YSI_Coding\y_hooks> // Always Create new HOOKING!
hook OnScriptInit()
{
    Command_AddAlt(YCMD:v, "veh");
    Command_AddAlt(YCMD:v, "vehicle");
    Command_AddAlt(YCMD:v, "vehicles");
    return 1;
}