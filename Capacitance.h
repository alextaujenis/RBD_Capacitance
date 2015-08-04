#ifndef CAPACITANCE_H
#define CAPACITANCE_H

#include <Arduino.h>

class Capacitance {
  public:
    Capacitance(int send_pin, int receive_pin);  // constructor
    void setSendPin(int pin);    // change the send pin
    void setReceivePin(int pin); // change the receive pin
    void update();               // update in real-time
    void startReading();         // kick off the process to take a single reading
    bool doneReading();          // return true if finished taking a single reading
    unsigned long getValue();    // returns the value of the single reading when done
  private:
    int _send_pin;
    int _receive_pin;
    bool _updating;
    bool _waiting;
    bool _finished;
    unsigned long _start;
    unsigned long _total_value;
    void _update();
};

#endif