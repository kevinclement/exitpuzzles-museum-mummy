#include "Arduino.h"
#include "EEPROM.h"
#include "logic.h"
#include "consts.h"

int LS_ONE = 0;                   // light sensor 1 reading
int LS_TWO = 0;                   // light sensor 2 reading

int LS_ONE_THRESH = 3700;
int LS_TWO_THRESH = 0;
int FOO_VAR_ADDR = 0;         // where to store foo in eeprom

Logic::Logic() 
  : serial(*this)
{
}

void Logic::setup() {
  serial.setup();

  readStoredVariables();

  serial.printHelp();
  printVariables();

  pinMode(13, OUTPUT);
  pinMode(34, INPUT);
  pinMode(39, INPUT);
}

void Logic::handle() {
  serial.handle();

  LS_ONE = analogRead(34);
  LS_TWO = analogRead(39);
  
  Serial.printf("1: %d 2: %d \n", LS_ONE, LS_TWO);
  if (LS_ONE > LS_ONE_THRESH) {
    Serial.println("LASER ON!");
    Serial.printf("0: %d 1: %d \n", LS_ONE, LS_TWO);
    digitalWrite(13, HIGH); //Turn led on
  }
  else {
    digitalWrite(13, LOW);  //Turn led off
  }

  delay(500);
}

void Logic::open() {

}

void Logic::close() {

}

void Logic::readStoredVariables() {
  EEPROM.begin(64); // don't need a big size
  //EEPROM.get(FOO_VAR_ADDR, FOO_VAR);
}

void Logic::printVariables() { 
  serial.print(CRLF);
  serial.print("Current Variables:%s", CRLF);
  serial.print("  ONE:  %d%s", LS_ONE, CRLF);
  serial.print("  TWO:  %d%s", LS_TWO, CRLF);
}