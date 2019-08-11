#include "Arduino.h"
#include "actuator.h"
#include "logic.h"

// motor control
#define PWMA 14
#define AIN1 15
#define AIN2 32
#define STBY 33

#define PRELOAD_TIME 5000

unsigned long preload_start = 0;

Actuator::Actuator(Logic &logic)
: _logic(logic)
{
}

void Actuator::setup() {
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
}

void Actuator::handle() {
  if (preload_start > 0 && millis() - preload_start > PRELOAD_TIME) {
    _logic.serial.print("preload finished.\n");
    preload_start = 0;
    stop();
  }
}

void Actuator::open() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(PWMA, HIGH);
  digitalWrite(STBY, HIGH);
}

void Actuator::close() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(PWMA, HIGH);
  digitalWrite(STBY, HIGH);
}

void Actuator::stop() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
}

void Actuator::preload() {
  preload_start = millis();
  open();
}
