#pragma once

#include "Arduino.h"

class Logic;

class Actuator {
  public:
    Actuator(Logic &logic);
    void setup();
    void handle();
    void open();
    void close();
    void stop();
    void preload();

  private:
    Logic &_logic;
};