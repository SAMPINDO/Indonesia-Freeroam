# List of APIs

## Callbacks

```c
OnPlayerAccountReady(playerid) // called when player's account is ready to use.

OnPlayerAttemptLogin(playerid, number_of_attempt) // called when registration of player's account success

OnPlayerRegisterSuccess(playerid) // called when registration of player's account success

OnPlayerLoginSuccess(playerid) // called when login success

OnPlayerSaveSuccess(playerid) // called when saving of player's account success
```

## Commands

```markdown
- /login
>> Log in to account.

- /register
>> Register your current username.

- /guest [username]
>> Switch current username to new username for register. (3 - 24 characters)
```

## Functions

```c
bool:Player_IsLoggedIn(playerid);

Player_ResetData(playerid);

bool:Player_HasMaximumLoginAttempt(playerid);

Player_InitORM(playerid);

void:Player_StartLoginTimeoutTimer(playerid);

bool:Player_IsDataLocked(playerid);

bool:Player_IsRegistered(playerid);

Player_InitGuestAccount(playerid);

Player_LoadAccount(playerid);

Player_SaveData(playerid, bool:release_lock = false);

Player_ShowLoginDialog(playerid);

Player_ShowRegisterDialog(playerid);

Player_ChangeUsername(playerid, const string:new_name[]);
```
