stock SendClientMessageEx(playerid, colour, const text[], va_args<>)
{
    new str[248];
    va_format(str, sizeof(str), text, va_start<3>);
    return SendClientMessage(playerid, colour, str);
}