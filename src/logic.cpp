#include "Arduino.h"
#include <HardwareSerial.h>
#include "EEPROM.h"
#include "logic.h"
#include "consts.h"

int FOO_VAR_ADDR = 0;         // where to store foo in eeprom

HardwareSerial MySerial(1);
static int8_t Send_buf[8] = {0};

Logic::Logic() 
  : serial(*this),
    actuator(*this),
    lights(*this),
    lightsensors(*this),
    sound(*this)
{
}

void sendCommand(int8_t command, int16_t dat);

void Logic::setup() {
  serial.setup();
  actuator.setup();
  lights.setup();
  lightsensors.setup();
  sound.setup();

  readStoredVariables();

  serial.printHelp();
  printVariables();

  MySerial.begin(9600, SERIAL_8N1, 16, 17);
  delay(500);              //Wait chip initialization is complete
  sendCommand(0X09, 0X02); // select the TF card
  delay(200);
  sendCommand(0X22, 0X4601);
}

void sendCommand(int8_t command, int16_t dat)
{
  delay(20);
  Send_buf[0] = 0x7e; //starting byte
  Send_buf[1] = 0xff; //version
  Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte
  Send_buf[3] = command; //
  Send_buf[4] = 0x00;//0x00 = no feedback, 0x01 = feedback
  Send_buf[5] = (int8_t)(dat >> 8);//datah
  Send_buf[6] = (int8_t)(dat); //datal
  Send_buf[7] = 0xef; //ending byte
  for(uint8_t i=0; i<8; i++)//
  {
    MySerial.write(Send_buf[i]);
  }
}

void Logic::handle() {
  serial.handle();
  lightsensors.handle();

  delay(500);
}

void Logic::readStoredVariables() {
  EEPROM.begin(64); // don't need a big size
  //EEPROM.get(FOO_VAR_ADDR, FOO_VAR);
}

void Logic::printVariables() { 
  serial.print(CRLF);
  serial.print("Current Variables:%s", CRLF);
}