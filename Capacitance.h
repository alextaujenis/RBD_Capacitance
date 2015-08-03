#ifndef CAPACITANCE_H
#define CAPACITANCE_H

#include <Arduino.h>

class Capacitance {
  public:
    Capacitance(int send_pin, int receive_pin);
    void update();
    void getValue();
    bool isFinished();
    unsigned long total();
  private:
    int _send_pin;
    int _receive_pin;
    bool _updating;
    bool _waiting;
    bool _finished;
    unsigned long _start;
    unsigned long _total;
    void _update();
};

#endif