#pragma once

#include "Arduino.h"

class Logic;

class Lights {
  public:
    Lights(Logic &logic);
    void setup();
    void handle();

    void on();
    void off();
    void allOn();

    bool lights_on = false;
    bool lights_all_on = false;
  private:
    Logic &_logic;
};