#define EMAIL_ADDRESS_LENGTH                  (255 + 1)
#define DISCORD_ID_LENGTH                     (20 + 1)
#define LOGIN_TIMEOUT_DURATION_IN_SECONDS     (60)
#define MAXIMUM_LOGIN_FAILED                  (3)



enum E_PLAYER_DATA
{
  // Database
  ORM:ORM_ID,
  ID,
  string:Username[MAX_PLAYER_NAME + 1],
  string:Password[BCRYPT_HASH_LENGTH],
  string:Email[EMAIL_ADDRESS_LENGTH],
  string:DiscordID[DISCORD_ID_LENGTH],
  DiscordBoundAt,
  AdminLevel,
  Money,
  Bank,
  Level,
  EXP,
  Kills,
  Deaths,
  ModelSkinID,
  PlayTime,
  VIPLevel,
  VIPExpiredAt,
  RegisteredAt,
  CreatedAt,
  UpdatedAt,

  // In-game
  bool:IsLoggedIn,
  PlayTimeStart,
  LoginAttempt,
  Timer:LoginTimer
};

new
  PlayerData[MAX_PLAYERS + 1][E_PLAYER_DATA]
;
