YCMD:v(playerid, params[], help)
{
    new vehicle;
    sscanf(params, "K<vehicle>(999)", vehicle);
    
    if(vehicle < 400 || vehicle > 611)
        return ShowVehicleTypeDialog(playerid);
    
    for(new i; i < sizeof(BlockedVehicle); i++)
    {
        if(vehicle == BlockedVehicle[i])
            return SEM(playerid, "Kendaraan ini tidak bisa di spawn.");
    }

    return SpawnVehicle(playerid, vehicle);
}