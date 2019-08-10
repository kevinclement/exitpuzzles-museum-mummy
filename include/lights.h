#pragma once

#include "Arduino.h"

class Logic;

class Lights {
  public:
    Lights(Logic &logic);
    void setup();

  private:
    Logic &_logic;
};