#include <sscanf2>
#include <YSI_Visual\y_commands>



CMD:login(playerid, params[], help)
{
  #pragma unused params

  if (Player_IsLoggedIn(playerid))
    return SendClientMessage(playerid, X11_TOMATO, "You are already logged in.");

  if (help)
  {
    SendClientMessage(playerid, X11_WHITE, "USAGE: /login");
    SendClientMessage(playerid, X11_WHITE, "USAGE: Log in to account.");
    return 1;
  }

  Player_ShowLoginDialog(playerid);
  return 1;
}

CMD:register(playerid, params[], help)
{
  #pragma unused params

  if (Player_IsLoggedIn(playerid))
    return SendClientMessage(playerid, X11_TOMATO, "You are already logged in.");

  if (help)
  {
    SendClientMessage(playerid, X11_WHITE, "USAGE: /register");
    SendClientMessage(playerid, X11_WHITE, "USAGE: Register your current username.");
    return 1;
  }

  Player_ShowRegisterDialog(playerid);
  return 1;
}

CMD:guest(playerid, params[], help)
{
  if (Player_IsLoggedIn(playerid))
    return SendClientMessage(playerid, X11_TOMATO, "You are already logged in.");

  if (help)
  {
    SendClientMessage(playerid, X11_WHITE, "USAGE: /guest [username]");
    SendClientMessage(playerid, X11_WHITE, "USAGE: Switch current username to new username for register. (3 - 24 characters)");
    return 1;
  }

  extract params -> new string:new_name[MAX_PLAYER_NAME + 1]; else
  {
    SendClientMessage(playerid, X11_WHITE, "USAGE: /guest [username]");
    SendClientMessage(playerid, X11_WHITE, "USAGE: Switch current username to new username for register. (3 - 24 characters)");
    return 1;
  }

  if (strlen(new_name) < 3)
    return SendClientMessage(playerid, X11_TOMATO, "Username too short! Minimum: 3 characters.");

  if (strlen > MAX_PLAYER_NAME)
    return SendClientMessage(playerid, X11_TOMATO, "Username too long! Maximum: 24 characters.");

  if (!Player_ChangeUsername(playerid))
    return SendClientMessage(playerid, X11_TOMATO, "Failed to change username.");

  va_SendClientMessage(playerid, X11_WHITE, "Your username changed to "LAWN_GREEN"%s"WHITE"");
  SendClientMessage(playerid, X11_WHITE, "Please register by command ("LAWN_GREEN"/register"WHITE") to get some benefits, like save your game progress.");
  return 1;
}
