#include "Arduino.h"
#include "consts.h"
#include "Logic.h"
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

SerialManager::SerialManager(Logic &logic)
: _logic(logic)
{  
}

void SerialManager::setup() {
  Serial.begin(115200);

  Serial.printf("Museum Mummy by kevinc...\n");

  // set read timeout to something really low so we don't hang
  Serial.setTimeout(10);

  while (!Serial); // Wait untilSerial is ready 

  // Bluetooth device name
  SerialBT.begin("ExitMuseumMummy");
}

void SerialManager::print(const char *fmt, ...) {
    char buf[128];     // resulting string limited to 128 chars
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, 128, fmt, args);
    va_end(args);

    // print to serial
    Serial.print(buf);

    // print to bluetooth if available
    SerialBT.print(buf);
}

void SerialManager::handle() {
    // read bluetooth messages
    readAnyBluetoothMessage();

    // read serial messages
    readAnySerialMessage();
}

void SerialManager::readAnyBluetoothMessage() {
  if (!SerialBT.available()) {
    return;
  }

  // read and handle message from bluetooth
  String str = SerialBT.readStringUntil('\n');
  handleMessage(str);
}

void SerialManager::readAnySerialMessage() {
  if (!Serial.available()) {
    return;
  }

  // read and handle message from serial
  String str = Serial.readStringUntil('\n');
  handleMessage(str);
}

void SerialManager::handleMessage(String msg) {
  Serial.print("got '");
  Serial.print(msg);
  Serial.println("' command");

  String command = msg;
  int value = -1;

  // check if we need to split on space for advance commands
  for (int i = 0; i <= msg.length(); i++) {
      if (msg.charAt(i) == ' ') {         
          command = msg.substring(0, i);
          value = msg.substring(i+1, msg.length()).toInt();
      }
  }
 
  if (command == "open" || command == "o") {
    _logic.open();
  }
  else if (command == "close" || command == "c") {
    _logic.close();
  }
  else if (command == "lightson" || command == "l") {
    _logic.lightsOn();
  }
  else if (command == "lightsall" || command == "a") {
    _logic.lights.allOn();
  }
  else if (command == "lightsoff" || command == "f") {
    _logic.lightsOff();
  }
  else if (command == "debug" || command == "d") {
    _logic.debug();
  }
  else if (command == "threshold") {
    print("setting threshold to '%d'...%s", value, CRLF);
    // LIGHT_THRESHOLD = value;
    // EEPROM.put(LIGHT_THRESHOLD_ADDR, value);
    // EEPROM.commit();    
  }
  else if (command == "status") {
    _logic.printVariables();
  }
  else if (command == "reset") {
    ESP.restart();
  } else {
    int str_len = command.length() + 1; 
    char char_array[str_len];
    command.toCharArray(char_array, str_len);
    print("unknown command: %s%s", char_array, CRLF);
  } 
}

void SerialManager::printHelp() {
  Serial.println("Available commands:");
  Serial.println("  open           - opens device");
  Serial.println("  close          - closes device");
  Serial.println("  foo N          - set foo to value N");
  Serial.println("  status         - prints the status of the device variables");
  Serial.println("  reset          - software reset the device");
}