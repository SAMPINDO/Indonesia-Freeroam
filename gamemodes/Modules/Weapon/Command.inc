YCMD:w(playerid, params[], help)
{
    if (!Player_IsLoggedIn(playerid))
        return SendClientMessage(playerid, X11_TOMATO, "You aren't already logged in.");

    new weapon;
    sscanf(params, "K<weapon>(999)", weapon);
    
    if(weapon < 1 || weapon > 46)
        return ShowWeaponSelectDialog(playerid);
    
    for(new i; i < sizeof(BlockedWeapons); i++)
    {
        if(weapon == BlockedWeapons[i])
            return SEM(playerid, "Weapon ini tidak bisa di spawn.");
    }

    return GivePlayerWeaponEx(playerid, weapon, 2000);
}