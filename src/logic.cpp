#include "Arduino.h"
#include <HardwareSerial.h>
#include "EEPROM.h"
#include "logic.h"
#include "consts.h"

int LS_ONE = 0;               // light sensor 1 reading
int LS_ONE_THRESH = 1800;
int LS_TWO = 0;               // light sensor 2 reading

int LS_TWO_THRESH = 0;
int FOO_VAR_ADDR = 0;         // where to store foo in eeprom

int freq = 5000;
int ledChannel = 0;
int resolution = 8;

// motor control
#define PWMA 14
#define AIN1 15
#define AIN2 32
#define STBY 33

// light sensors
#define LS_ONE_PIN A2
#define LS_TWO_PIN A3

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

  readStoredVariables();

  serial.printHelp();
  printVariables();

  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(27, ledChannel);

  pinMode(LS_ONE_PIN, INPUT);
  pinMode(LS_TWO_PIN, INPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(STBY, OUTPUT);

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

void turnOnLights() {
  // for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
  //   ledcWrite(ledChannel, dutyCycle);
  //   delay(7);
  // }
 
  // for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
  //   ledcWrite(ledChannel, dutyCycle);
  //   delay(7);
  // }
}

void open() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(PWMA, HIGH);
  digitalWrite(STBY, HIGH);
}

void close() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(PWMA, HIGH);
  digitalWrite(STBY, HIGH);
}

void Logic::handle() {
  serial.handle();

  LS_ONE = analogRead(LS_ONE_PIN);
  LS_TWO = analogRead(LS_TWO_PIN);
  
  Serial.printf("1: %d 2: %d \n", LS_ONE, LS_TWO);
  if (LS_ONE > LS_ONE_THRESH) {
     Serial.println("LASER ON!");
  }
  else {
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