YCMD:w(playerid, params[], help)
{
    if (!Player_IsLoggedIn(playerid))
        return SendClientMessage(playerid, X11_TOMATO, "You aren't already logged in.");

    return ShowWeaponSelectDialog(playerid);
}