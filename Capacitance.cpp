#include <Arduino.h>
#include <Capacitance.h>

Capacitance::Capacitance(int send_pin, int receive_pin) {
  // save local variables
  _send_pin    = send_pin;
  _receive_pin = receive_pin;

  // set beginning state
  _updating = false;
  _waiting  = false;
  _finished = true;

  // set send pin to output
  pinMode(_send_pin, OUTPUT);
  // turn off the send pin
  digitalWrite(_send_pin, LOW);
}

void Capacitance::update() {
  if(_updating) {
    _update();
  }
}

void Capacitance::startReading() {
  _updating = true;
  _waiting  = false;
  _finished = false;
}

bool Capacitance::doneReading() {
  return _finished;
}

unsigned long Capacitance::getValue() {
  return _total_value;
}

void Capacitance::setSendPin(int pin) {
  _send_pin = pin;
}

void Capacitance::setReceivePin(int pin) {
  _receive_pin = pin;
}

void Capacitance::_update() {
  if(!_waiting) {
    // DISCHARGE
    // set receive pin to output
    pinMode(_receive_pin, OUTPUT);
    // set receive pin to low (ground)
    digitalWrite(_receive_pin, LOW);
    // set the receive pin back up to input
    pinMode(_receive_pin, INPUT);
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
    // stop updating
    _updating = false;
    // finished
    _finished = true;
  }
}