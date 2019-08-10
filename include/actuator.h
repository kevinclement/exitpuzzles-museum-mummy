#pragma once

#include "Arduino.h"

class Logic;

class Actuator {
  public:
    Actuator(Logic &logic);
    void setup();
    void open();
    void close();

  private:
    Logic &_logic;
};