// Gestione RGB led catodo comune
//      R   C   G   B
// GPIO 14  Gr  12  13
//
const int redPin    =  14;
const int greenPin  =  12;
const int bluePin   =  13;
#define LED_OFF   4
const int freq          = 12000;
const int redChannel    = 0;
const int greenChannel  = 1;
const int blueChannel   = 2;
// Bit resolution 2^8 = 256
const int resolution = 8;

uint8_t colors[5][3] = {{0,255,0}, {255,0,0}, {255,0,255}, {255,255,255}, {0,0,0}};

void init_led(){
  // configure LED PWM functionalitites
  ledcSetup(redChannel, freq, resolution);
  ledcSetup(greenChannel, freq, resolution);
  ledcSetup(blueChannel, freq, resolution);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(redPin, redChannel);
  ledcAttachPin(greenPin, greenChannel);
  ledcAttachPin(bluePin, blueChannel);
}
//
void set_led(unsigned char col_tab){
  for(uint8_t i=0;i<3;i++){
    ledcWrite(i, colors[col_tab][i]);
  }
}
