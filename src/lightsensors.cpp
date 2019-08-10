#include "Arduino.h"
#include "lightsensors.h"

int LS_ONE = 0;               // light sensor 1 reading
int LS_ONE_THRESH = 1800;
int LS_TWO = 0;               // light sensor 2 reading
int LS_TWO_THRESH = 0;

// light sensors
#define LS_ONE_PIN A2
#define LS_TWO_PIN A3

LightSensors::LightSensors(Logic &logic)
: _logic(logic)
{  
}

void LightSensors::setup() {
  pinMode(LS_ONE_PIN, INPUT);
  pinMode(LS_TWO_PIN, INPUT);
}

void LightSensors::handle() {
  LS_ONE = analogRead(LS_ONE_PIN);
  LS_TWO = analogRead(LS_TWO_PIN);

  Serial.printf("1: %d 2: %d \n", LS_ONE, LS_TWO);

  // TODO: debounce
  if (LS_ONE > LS_ONE_THRESH) {
     Serial.println("LASER ON!");
  }
  else {
  }
}
