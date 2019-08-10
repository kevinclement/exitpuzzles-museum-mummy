#pragma once

#include "Arduino.h"

class Logic;

class LightSensors {
  public:
    LightSensors(Logic &logic);
    void setup();

  private:
    Logic &_logic;
};