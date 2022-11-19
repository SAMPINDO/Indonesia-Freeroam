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
