#include "Arduino.h"
#include "logic.h"
#include "consts.h"

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

  delay(500);
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