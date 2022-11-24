
stock GivePlayerWeaponEx(playerid, wepid, ammocount)
{
    GivePlayerWeapon(playerid, wepid, ammocount);
    return 1;
}
stock ShowWeaponSelectDialog(playerid)
{
    inline WeaponResponse(pid, dialogid, response, listitem, string:inputtext[])
    {
        #pragma unused dialogid, inputtext, pid
        if(response)
        {
            switch(listitem)
            {
                case 0:
                {
                    if(weaponSelected[playerid][0] == 1)
                        return SEM(playerid, "Selected ini sudah anda pilih sebelumnya");

                    ResetPlayerWeapons(playerid);
                    GivePlayerWeaponEx(playerid, 16, 1500);
                    GivePlayerWeaponEx(playerid, 24, 1500);
                    GivePlayerWeaponEx(playerid, 25, 1500);
                    GivePlayerWeaponEx(playerid, 27, 1500);
                    GivePlayerWeaponEx(playerid, 30, 1500);
                    weaponSelected[playerid][0] = 1;
                    weaponSelected[playerid][1] = 0;
                    weaponSelected[playerid][2] = 0;
                }
                case 1:
                {
                    if(weaponSelected[playerid][1] == 1)
                        return SEM(playerid, "Selected ini sudah anda pilih sebelumnya");
                        
                    ResetPlayerWeapons(playerid);
                    GivePlayerWeaponEx(playerid, 17, 1500);
                    GivePlayerWeaponEx(playerid, 23, 1500);
                    GivePlayerWeaponEx(playerid, 26, 1500);
                    GivePlayerWeaponEx(playerid, 29, 1500);
                    GivePlayerWeaponEx(playerid, 31, 1500);
                    weaponSelected[playerid][1] = 1;
                    weaponSelected[playerid][0] = 0;
                    weaponSelected[playerid][2] = 0;
                }
                case 2:
                {
                    if(weaponSelected[playerid][2] == 1)
                        return SEM(playerid, "Selected ini sudah anda pilih sebelumnya");
                        
                    ResetPlayerWeapons(playerid);
                    GivePlayerWeaponEx(playerid, 18, 1500);
                    GivePlayerWeaponEx(playerid, 24, 1500);
                    GivePlayerWeaponEx(playerid, 27, 1500);
                    GivePlayerWeaponEx(playerid, 32, 1500);
                    GivePlayerWeaponEx(playerid, 34, 1500);
                    weaponSelected[playerid][2] = 1;
                    weaponSelected[playerid][0] = 0;
                    weaponSelected[playerid][1] = 0;
                }
            }
        }
    }
    Dialog_ShowCallback(playerid, using inline WeaponResponse, DIALOG_STYLE_TABLIST, "Weapon Selection", sprintf("Weapon A\t%s\nWeapon B\t%s\nWeapon C\t%s", (!weaponSelected[playerid][0]) ? ("Grenade/9mm/Shotgun/Uzi/AK47") : (""RED"Selected"), (!weaponSelected[playerid][1]) ? ("Tear Gas/Silinced Pistol/Sawnoff Shotgun/MP5/M4") : (""RED"Selected"), (!weaponSelected[playerid][2]) ? ("Molotov/Deagle/Combat Shotgun/Tec-9/Sniper") : (""RED"Selected")), "Select", "Cancel");
    return 1;
}

stock RandomWeaponSpawn(playerid)
{
    switch(random(3))
    {
        case 0:
        {
            if(weaponSelected[playerid][0] == 1)
                return SEM(playerid, "Selected ini sudah anda pilih sebelumnya");

            ResetPlayerWeapons(playerid);
            GivePlayerWeaponEx(playerid, 16, 1500);
            GivePlayerWeaponEx(playerid, 24, 1500);
            GivePlayerWeaponEx(playerid, 25, 1500);
            GivePlayerWeaponEx(playerid, 27, 1500);
            GivePlayerWeaponEx(playerid, 30, 1500);
            weaponSelected[playerid][0] = 1;
            weaponSelected[playerid][1] = 0;
            weaponSelected[playerid][2] = 0;
        }
        case 1:
        {
            if(weaponSelected[playerid][1] == 1)
                return SEM(playerid, "Selected ini sudah anda pilih sebelumnya");
                        
            ResetPlayerWeapons(playerid);
            GivePlayerWeaponEx(playerid, 17, 1500);
            GivePlayerWeaponEx(playerid, 23, 1500);
            GivePlayerWeaponEx(playerid, 26, 1500);
            GivePlayerWeaponEx(playerid, 29, 1500);
            GivePlayerWeaponEx(playerid, 31, 1500);
            weaponSelected[playerid][1] = 1;
            weaponSelected[playerid][0] = 0;
            weaponSelected[playerid][2] = 0;
        }
        case 2:
        {
            if(weaponSelected[playerid][2] == 1)
                return SEM(playerid, "Selected ini sudah anda pilih sebelumnya");
                        
            ResetPlayerWeapons(playerid);
            GivePlayerWeaponEx(playerid, 18, 1500);
            GivePlayerWeaponEx(playerid, 24, 1500);
            GivePlayerWeaponEx(playerid, 27, 1500);
            GivePlayerWeaponEx(playerid, 32, 1500);
            GivePlayerWeaponEx(playerid, 34, 1500);
            weaponSelected[playerid][2] = 1;
            weaponSelected[playerid][0] = 0;
            weaponSelected[playerid][1] = 0;
        }
    }
    return 1;
}