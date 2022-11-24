#include <YSI_Coding\y_hooks> // Always Create new HOOKING!
hook OnPlayerDisconnect(playerid, reason)
{
    #pragma unused reason

    weaponSelected[playerid][0] = 0;
    weaponSelected[playerid][1] = 0;
    weaponSelected[playerid][2] = 0;
    return 1;
}
