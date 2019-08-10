#include "Arduino.h"
#include "lights.h"

const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

Lights::Lights(Logic &logic)
: _logic(logic)
{  
}

void Lights::on() {
  Serial.println("on");

  // for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
  //   ledcWrite(ledChannel, dutyCycle);
  //   delay(7);
  // }
 
  // for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
  //   ledcWrite(ledChannel, dutyCycle);
  //   delay(7);
  // }
}

void Lights::off() {
  Serial.println("off");
}

void Lights::setup() {
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(27, ledChannel);
}
