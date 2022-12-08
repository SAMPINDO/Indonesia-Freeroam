#include <YSI_Coding\y_timers>



timer Player_KickDelayed[500](playerid)
{
    return Kick(playerid);
}

timer Player_KickLoginTimeout[LOGIN_TIMEOUT_DURATION_IN_SECONDS * 1_000](playerid)
{
    SendClientMessage(playerid, X11_TOMATO, "You were kicked because of login timeout.");
    defer Player_KickDelayed(playerid);
    return 1;
}

timer Player_RegainGodModeBenefit[1_000](playerid)
{
    if (playerid < 0 || playerid > MAX_PLAYERS)
    {
        printf("[WARN] God mode running with invalid player ID: %d", playerid);
        return 1;
    }

    if (!IsPlayerConnected(playerid) && Timer_IsRunning(PlayerData[playerid][GodModeBenefitTimer]))
    {
        stop PlayerData[playerid][GodModeBenefitTimer];
        PlayerData[playerid][GodModeBenefitTimer] = Timer:0;
        return 1;
    }

    SetPlayerHealth(playerid, 1_000_000.0);

    new vehicleid = GetPlayerVehicleID(playerid);

    // Jika player keluar dari kendaraan, maka kendaraan yang terakhir player ...
    // ... naik akan diubah kembali ke health normal-nya.
    if (vehicleid == 0 && PlayerData[playerid][LastVehicleID] != INVALID_VEHICLE_ID)
    {
        RepairVehicle(PlayerData[playerid][LastVehicleID]);
        SetVehicleHealth(PlayerData[playerid][LastVehicleID], 1_000.0);
    }

    if (PlayerData[playerid][LastVehicleID] != vehicleid)
    {
        PlayerData[playerid][LastVehicleID] = vehicleid;
    }

    if (PlayerData[playerid][LastVehicleID] != INVALID_VEHICLE_ID)
    {
        RepairVehicle(PlayerData[playerid][LastVehicleID]);
        SetVehicleHealth(PlayerData[playerid][LastVehicleID], 100_000.0);
    }

    return 1;
}
