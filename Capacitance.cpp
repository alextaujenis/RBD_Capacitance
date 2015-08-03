#include <Arduino.h>
#include <Capacitance.h>

Capacitance::Capacitance(int send_pin, int receive_pin) {
  // save local variables
  _send_pin    = send_pin;
  _receive_pin = receive_pin;

  // STARTUP
  // set send pin to output
  pinMode(_send_pin, OUTPUT);
  // turn off the send pin
  digitalWrite(_send_pin, LOW);
}

unsigned long Capacitance::getValue() {
  // DISCHARGE
  // set receive pin to output
  pinMode(_receive_pin, OUTPUT);
  // set receive pin to low (ground)
  digitalWrite(_receive_pin, LOW);
  // set the receive pin back up to input
  pinMode(_receive_pin, INPUT);

  // CHARGE
  // start counter
  _start = micros();
  // turn on the send pin
  digitalWrite(_send_pin, HIGH);
  // wait until the receive pin is on
  while (!digitalRead(_receive_pin)) {} // do nothing
  // turn off the send pin
  digitalWrite(_send_pin, LOW);
  // report the time in microseconds
  return micros() - _start;
}