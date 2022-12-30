unsigned char STATO;
#define OZIOSO  0
#define TESTING 1
#define FINITO  2
#define AGGWIFI 3
//
#ifdef DEBUG
  #define DEBUG_PRINT(x)    Serial.print(x)
  #define DEBUG_PRINTDEC(x) Serial.print(x, DEC)
  #define DEBUG_PRINTLN(x)  Serial.println(x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTDEC(x)
  #define DEBUG_PRINTLN(x)
#endif
//
