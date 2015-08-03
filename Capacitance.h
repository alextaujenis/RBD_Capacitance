#ifndef CAPACITANCE_H
#define CAPACITANCE_H

#include <Arduino.h>

class Capacitance {
  public:
    Capacitance(int send_pin, int receive_pin);
    unsigned long getValue();
  private:
    int _send_pin;
    int _receive_pin;
    unsigned long _start;
};

#endif