#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
//
int timeout = 120; // seconds to run for
String hostname = "ESP32Mahler";
const char* APEsp32 = "MahlerAP";
//
bool start_wifi(){
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP 
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
  WiFi.setHostname(hostname.c_str()); //define hostname
  //
  WiFiManager wm;
  //wm.resetSettings();
  wm.setConfigPortalTimeout(timeout);
  //wm.resetSettings();
  // Define a text box, 50 characters maximum
  //WiFiManagerParameter custom_text_box("my_text", "Inviare risultati a:", RECIPIENT1, 50);
  WiFiManagerParameter custom_text_box("my_text", "Inviare risultati a:", recipient, 50);
  // Add custom parameter
  wm.addParameter(&custom_text_box);  
  //  
  bool res;
  res = wm.autoConnect(APEsp32); // password protected ap
  if(!res) {
    DEBUG_PRINTLN("Failed to connect");
    ESP.restart();
  }
  strncpy(recipient,custom_text_box.getValue(), sizeof(recipient));
  DEBUG_PRINT("Inviare mail dati a: ");
  DEBUG_PRINTLN(recipient);
  //if you get here you have connected to the WiFi
  DEBUG_PRINTLN("Connesso...");  
  delay(2000);
  //ESP.restart();}  
}
void check_portal_chg(){
    // is configuration portal requested?
    WiFiManager wm; 
    //wm.resetSettings();
    wm.setConfigPortalTimeout(timeout);
    //wm.resetSettings();
    // Define a text box, 50 characters maximum
    WiFiManagerParameter custom_text_box("my_text", "Inviare risultati a:", recipient, 50);
    // Add custom parameter
    wm.addParameter(&custom_text_box);  
    delay(500);
    //reset settings - for testing
    //wm.resetSettings();
    // set configportal timeout
    wm.setConfigPortalTimeout(timeout);
    if (!wm.startConfigPortal(APEsp32)) {
      DEBUG_PRINTLN("failed to connect and hit timeout");
      delay(3000);
      //reset and try again, or maybe put it to deep sleep
      delay(5000);
      ESP.restart();
    }  
    delay(500);
    strncpy(recipient,custom_text_box.getValue(), sizeof(recipient));
    DEBUG_PRINT("Inviare mail dati a: ");
    DEBUG_PRINTLN(recipient);
    //if you get here you have connected to the WiFi
    DEBUG_PRINTLN("Connesso...");  
    delay(2000);
}
