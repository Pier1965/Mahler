/************************************************
  Pierpaolo Garofalo - http://pier.unirc.eu
  Licensed under GNU GPL v3
  29.12.2022
*************************************************
1) 24.12.2022 Il wifimanager funziona
2) 25.12.2022 Sensore temperatura 18B20 funziona
3) 26.12.2022 Invio file mail dati temp ok
4) 28.12.2022 Gestione pressione pulsante
5) 28.12.2022 Gestione OLED
6) 29.12.2022 Gestione LED RGB
7) 20.01.2023 Gestione inserimento mail invio dati
*************************************************/
#define DEBUG // NODEBUG
#define MAIL  // NOMAIL
//
#include "include.h"
//
void setup() {
  init_led();
  //
  init_button();
  //
  #ifdef DEBUG
    Serial.begin(115200);
    DEBUG_PRINTLN("\n Starting");
  #endif
  //
  initSCR();
  // 
  printSCR_attesaWL();
  if(start_wifi())
    printSCR_yesnet();
  else
    printSCR_nonet();
  delay(2000);
  //
  initTime();
  //
  start_sensor();
  //
  SPIFFS.begin();
  //
  STATO = OZIOSO;
}
//
 void loop() {
  delay(1000);
  update_STATO();
  // Aggiornare i dati accesso WIFI?
  for(;STATO == OZIOSO;){
    print_temperatura_SCR();
    chk_button();
    set_led(STATO);
    delay(50);
    set_led(LED_OFF);
    delay(200);
  }
  if(STATO == AGGWIFI){
    DEBUG_PRINTLN("Configurazione WIFI");
    update_STATO();
    check_portal_chg();
    delay(1000);
    DEBUG_PRINTLN("Configurazione WIFI eseguita");
    STATO = OZIOSO;
    update_STATO();
    //ESP.restart();
  } else
  if(STATO == TESTING){
    update_STATO();
    DEBUG_PRINTLN("Inizio rilievo temperature");
    do_test();
    DEBUG_PRINTLN("Rilievo temperature finito");
    STATO = FINITO;
  } else 
  if(STATO == FINITO){
    update_STATO();
    DEBUG_PRINTLN("Invio mail...");
    #ifdef MAIL
      send_mail();
    #endif
    DEBUG_PRINTLN("Mail inviata");
    delay(1000);
    STATO = OZIOSO;
  }
}
//
