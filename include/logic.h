#pragma once

#include "SerialManager.h"

class Logic {
public:
  Logic();
  SerialManager serial;

  void setup();
  void handle();
  void printVariables();
  void open();
  void close();

private:
  void readStoredVariables();
  
};

