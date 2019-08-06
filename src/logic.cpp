#include "Arduino.h"
#include "EEPROM.h"
#include "logic.h"
#include "consts.h"

int LS_ONE = 0;                   // light sensor 1 reading
int LS_TWO = 0;                   // light sensor 2 reading

int LS_ONE_THRESH = 3700;
int LS_TWO_THRESH = 0;
int FOO_VAR_ADDR = 0;         // where to store foo in eeprom

// motor control
#define PWMA 14
#define AIN1 15
#define AIN2 32
#define STBY 33

Logic::Logic() 
  : serial(*this)
{
}

void Logic::setup() {
  serial.setup();

  readStoredVariables();

  serial.printHelp();
  printVariables();

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
}

void Logic::handle() {
  serial.handle();

  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);

  digitalWrite(PWMA, HIGH);
  digitalWrite(STBY, HIGH);

  // LS_ONE = analogRead(34);
  // LS_TWO = analogRead(39);
  
  // Serial.printf("1: %d 2: %d \n", LS_ONE, LS_TWO);
  // if (LS_ONE > LS_ONE_THRESH) {
  //   Serial.println("LASER ON!");
  //   Serial.printf("0: %d 1: %d \n", LS_ONE, LS_TWO);
  //   digitalWrite(13, HIGH); //Turn led on
  // }
  // else {
  //   digitalWrite(13, LOW);  //Turn led off
  // }

  // delay(500);
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