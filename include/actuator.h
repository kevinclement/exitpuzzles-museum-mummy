#pragma once

#include "Arduino.h"

class Logic;

class Actuator {
  public:
    Actuator(Logic &logic);
    void setup();

  private:
    Logic &_logic;
};