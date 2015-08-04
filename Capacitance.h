#ifndef CAPACITANCE_H
#define CAPACITANCE_H

#include <Arduino.h>

class Capacitance {
  public:
    Capacitance(int send_pin, int receive_pin); // constructor
    void update();                // update in real-time
    void setSendPin(int pin);     // change the send pin
    void setReceivePin(int pin);  // change the receive pin
    void setSampleSize(int size); // how many readings to take per cycle
    void startCycling();          // begin a cycle (take sample_size readings)
    bool doneCycling();           // the cycle is finished (sample_size readings have been taken)
    unsigned long getAverage();   // updated after a cycle is finished with the moving average of cycle time
  private:
    int _send_pin;
    int _receive_pin;
    int _sample_size = 100;         // how many readings should be taken for one cycle
    int _cycle_count = 0;           // how many readings have been taken for the current cycle
    bool _cycling    = false;       // true if in the middle of a cycle
    bool _waiting    = false;       // true if in the middle of a reading
    bool _finished   = true;        // true if finished with one reading
    unsigned long _sample_sum = 0;  // temp value that holds the sum of all readings for this cycle
    unsigned long _start;           // the time in microseconds that a reading was started
    unsigned long _total_value;     // the time in microseconds how long a reading took
    unsigned long _total_average;   // the average time in microseconds for the last sample_size number of readings
    unsigned long _getValue();      // returns the value of the single reading when done
    void _startReading();           // kick off the process to take a single reading
    bool _doneReading();            // return true if finished taking a single reading
    void _update();                 // perform the actual reading
    void _cycle();                  // perform x number of readings
};

#endif