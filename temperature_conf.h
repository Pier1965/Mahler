#include <OneWire.h>
#include <DallasTemperature.h>
#include "parametri_prova.h"
#define TEMPERATURE_PRECISION 12  // higher resolution
float T[N_SAMPLINGS];
unsigned int N_SAMP_DONE = 0;     // misurazioni fatte in caso di interruzione prova anticipata
// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;    
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire); 
DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address
//
void start_sensor(){
  // Start the DS18B20 sensor
  sensors.begin();
  // set the resolution to TEMPERATURE_PRECISION bit (Each Dallas/Maxim device is capable of several different resolutions)
  sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);
}
//
void get_temperature(int i){
  sensors.requestTemperatures(); 
  T[i]=sensors.getTempCByIndex(0);
}
//
void writeTempToFile(){
  DEBUG_PRINTLN("Scrittura dati su file"); 
  File file_temperature = SPIFFS.open("/fileDati.txt", FILE_WRITE);
  for (int n = 0; n < N_SAMP_DONE; n++) {
    float temp = float(n)*float(DT_SAMPLINGS)/1000;
    file_temperature.print(temp);
    file_temperature.print(" ");
    file_temperature.println(T[n]);
  }
  file_temperature.close();
  DEBUG_PRINTLN("Fatto...");
}
//
void readTempToFile(){
  DEBUG_PRINTLN("Lettura dati su file"); 
  File file_temperature = SPIFFS.open("/fileDati.txt");
  if(!file_temperature){
  DEBUG_PRINTLN("There was an error opening the file for reading");
return;
  }
  while(file_temperature.available()){
    Serial.write(file_temperature.read());
  }
  file_temperature.close();
  DEBUG_PRINTLN("Fatto...");
}
//
void do_test(){
  N_SAMP_DONE = 0;
    for (int i=0;((i<N_SAMPLINGS)&&(STATO == TESTING));i++){
      get_temperature(i);
      N_SAMP_DONE = i+1;
      DEBUG_PRINT(T[i]);
      DEBUG_PRINTLN("ºC");
      String str = String(i) + ":" + String(T[i]) + "C";
      printSCR_lettura(str);
      unsigned long t_init = millis();
      for(;((millis()- t_init)<DT_SAMPLINGS);){
        chk_button();
      }
      str="           ";
      printSCR_lettura(str);
    }
    DEBUG_PRINTLN("------------------------");
    for(int i=0;i<N_SAMP_DONE;i++){
      DEBUG_PRINT(T[i]);
      DEBUG_PRINTLN("ºC");
    }
    writeTempToFile();
}
//
void print_temperatura_SCR(){
  get_temperature(0);
  String str = "T:" + String(T[0]) + "C";
  printSCR_lettura(str);
}
