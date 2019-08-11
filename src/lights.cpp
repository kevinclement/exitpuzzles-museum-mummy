#include "Arduino.h"
#include "lights.h"

#define BETWEEN 2579
#define DURATION 43 
#define TIMES 7
#define FREQ 5000
#define RES 8
#define CHANNEL 0

Lights::Lights(Logic &logic)
: _logic(logic)
{  
}

bool lights_on = false;
unsigned long lastTime = 0;
int waitTime = 0;

void flash() {
  int tl = abs(esp_random()) % TIMES + 1;
  int dl = abs(esp_random()) % DURATION + 1;

  for (int i=0; i<tl; i++)
  {
    ledcWrite(CHANNEL, 255);
    delay(40 + dl);
    ledcWrite(CHANNEL, 0);
    delay(10);
  }
}

void Lights::on() {
  Serial.println("Turning lights on...");
  lights_on = true;
}

void Lights::off() {
  Serial.println("Turning lights off...");
  ledcWrite(CHANNEL, 0);
  lights_on = false;
}

void Lights::setup() {
  ledcSetup(CHANNEL, FREQ, RES);
  ledcAttachPin(27, CHANNEL);
}

void Lights::handle() {
  if (lights_on) {
    if (millis() - waitTime > lastTime)  // time for a new flash
    {
      // adjust timing params
      lastTime += waitTime;
      waitTime = abs(esp_random()) % BETWEEN + 1;

      flash();
    }
  }
}
