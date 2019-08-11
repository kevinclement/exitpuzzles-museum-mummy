#include "Arduino.h"
#include "logic.h"
#include "consts.h"

#define TIME_TO_OPEN 40000

bool SOLVED = false;
unsigned long solved_at = 0;

Logic::Logic() 
  : serial(*this),
    actuator(*this),
    lights(*this),
    lightsensors(*this),
    sound(*this)
{
}

void Logic::setup() {
  serial.setup();
  actuator.setup();
  lights.setup();
  lightsensors.setup();
  sound.setup();

  readStoredVariables();

  serial.printHelp();
  printVariables();
}

void Logic::handle() {
  serial.handle();
  lightsensors.handle();
  lights.handle();
  actuator.handle();

  if (lightsensors.lightDetected && !SOLVED) {
    serial.print("Solved!\n");

    sound.play();
    lights.on();
    actuator.open();

    SOLVED = true;
    solved_at = millis();
  }


}

void Logic::readStoredVariables() {
  //EEPROM.begin(64); // don't need a big size
  //EEPROM.get(FOO_VAR_ADDR, FOO_VAR);
}

void Logic::printVariables() { 
  serial.print(CRLF);
  serial.print("Current Variables:%s", CRLF);
}