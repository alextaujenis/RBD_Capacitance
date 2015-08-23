#include <Arduino.h>
#include <Capacitance.h>

Capacitance::Capacitance(int send_pin, int receive_pin) {
  setSendPin(send_pin);
  setReceivePin(receive_pin);
}

void Capacitance::setSendPin(int pin) {
  // only change if needed
  if (_send_pin != pin) {
    // save the local value
    _send_pin = pin;
    // set send pin to output
    pinMode(_send_pin, OUTPUT);
    // turn off the send pin
    digitalWrite(_send_pin, LOW);
  }
}

void Capacitance::setReceivePin(int pin) {
  _receive_pin = pin;
}

void Capacitance::setSampleSize(int size) {
  // set the sample size
  _sample_size = size;
  // restart the cycle variables
  _sample_sum  = 0;
  _cycle_count = 0;
}

void Capacitance::start() {
  _startCycling();
}

void Capacitance::update() {
  if(_cycling) {
    _cycle();
  }
}

bool Capacitance::isFinished() {
  return _doneCycling();
}

unsigned long Capacitance::value() {
  return _getAverage();
}


// private

void Capacitance::_startCycling() {
  _cycling = true; // taking many readings
  _startReading();
}

bool Capacitance::_doneCycling() {
  return !_cycling;
}

void Capacitance::_startReading() {
  _waiting  = false; // in the middle of a reading
  _finished = false; // finished with a reading
}

bool Capacitance::_doneReading() {
  return _finished;
}

unsigned long Capacitance::_getValue() {
  return _total_value; // current reading value
}

unsigned long Capacitance::_getAverage() {
  return _total_average; // average of many reading values
}

void Capacitance::_update() {
  if(!_waiting) {
    // CHARGE
    // start waiting
    _waiting = true;
    // turn on the send pin
    digitalWrite(_send_pin, HIGH);
    // start counter
    _start = micros();
  }

  // wait until the receive pin is on
  if(_waiting && bool(digitalRead(_receive_pin))) {
    // save the time in microseconds
    _total_value = micros() - _start;
    // turn off the send pin
    digitalWrite(_send_pin, LOW);
    // DISCHARGE
    // set receive pin to output
    pinMode(_receive_pin, OUTPUT);
    // set receive pin to low (ground)
    digitalWrite(_receive_pin, LOW);
    // set the receive pin back up to input
    pinMode(_receive_pin, INPUT);
    // finished
    _finished = true;
  }
}

void Capacitance::_cycle() {
  // keep reading
  _update();

  // when a single reading has been collected
  if(_doneReading()) {
    // check if we can take another reading for this cycle
    if(_cycle_count < _sample_size) {
      // sum the reading
      _sample_sum += _getValue();
      _cycle_count++;
      // restart the reading process again
      _startReading();
    }
    // no more readings for this cycle
    else {
      // save a moving average
      _total_average = _sample_sum / _sample_size;
      // reset counter variables
      _sample_sum  = 0;
      _cycle_count = 0;
      // stop cycling
      _cycling = false;
    }
  }
}