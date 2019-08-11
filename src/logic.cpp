#include "Arduino.h"
#include "logic.h"
#include "consts.h"

bool SOLVED = false;

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

  if (lightsensors.lightDetected && !SOLVED) {
    serial.print("Solved!\n");

    actuator.open();
    lights.on();

    SOLVED = true;
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

void Logic::lightsOn() {
  lights.on();
}

void Logic::lightsOff() {
  lights.off();
}

void Logic::open() {
  actuator.open();
}

void Logic::close() {
  actuator.close();
}

void Logic::debug() {
  serial.print("Toggling debug mode...%s", CRLF);
  lightsensors.debugReadings = !lightsensors.debugReadings;
}