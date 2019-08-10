#pragma once

#include "Arduino.h"

class Logic;

class Sound {
  public:
    Sound(Logic &logic);
    void setup();

  private:
    Logic &_logic;
};