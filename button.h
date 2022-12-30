/*
  ----------------------------
  | Pulsanti         | ESP32  |
  ----------------------------
  | Pulsante         | D02    |
  ----------------------------
*/
#define VERY_SHORT_PRESS_TIME 200   // debump filtro
#define SHORT_PRESS_TIME 1000       // 1000 milliseconds
#define LONG_PRESS_TIME 5000        // 5000 milliseconds
// Variables will change:
int lastState = LOW;  // the previous state from the input pin
int currentState;     // the current reading from the input pin
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;
//
void init_button(){
  pinMode(TRIGGER_PIN, INPUT);
}
void chk_button(){
  currentState = digitalRead(TRIGGER_PIN);
  if (lastState == LOW && currentState == HIGH)       // fronte di salita
    pressedTime = millis();
  else if (lastState == HIGH && currentState == LOW) { // fronte di discesa
    releasedTime = millis();
    long pressDuration = releasedTime - pressedTime;
    if ((pressDuration > LONG_PRESS_TIME) && (STATO == OZIOSO)){
      STATO = AGGWIFI;
      update_STATO();
      DEBUG_PRINTLN(pressDuration);}
    else if (((pressDuration > SHORT_PRESS_TIME) && (pressDuration < LONG_PRESS_TIME)) && (STATO == TESTING)){
      STATO = FINITO;
      update_STATO();
      DEBUG_PRINTLN("Fine prova anticipata");
      DEBUG_PRINTLN("A short press is detected");
      DEBUG_PRINTLN(pressDuration);}
    else if (((pressDuration > VERY_SHORT_PRESS_TIME) && (pressDuration < SHORT_PRESS_TIME)) && (STATO == OZIOSO)){
      STATO = TESTING;
      update_STATO();
      DEBUG_PRINTLN("Inizio rilevazione temperature");
      DEBUG_PRINTLN("An impulse press is detected");
      DEBUG_PRINTLN(pressDuration);}
  }
  // save the the last state
  lastState = currentState;
}
