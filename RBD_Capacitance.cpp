// Arduino RBD_Capacitance Library - A real-time library for determining relative capacitance
// Copyright 2015 Alex Taujenis
// MIT License

#include <Arduino.h>
#include <RBD_Capacitance.h>

RBD_Capacitance::RBD_Capacitance(int send_pin, int receive_pin) {
  // set send pin
  _send_pin = send_pin;
  // set receive pin
  _receive_pin = receive_pin;
  // set send pin to output
  pinMode(_send_pin, OUTPUT);
  // turn off the send pin
  digitalWrite(_send_pin, LOW);
}

void RBD_Capacitance::setSampleSize(int size) {
  if(size > 0) {
    // set the sample size
    _sample_size = size;
    // reset the sample variables
    _sample_sum   = 0;
    _sample_count = 0;
  }
}

void RBD_Capacitance::start() {
  _startSampling();
}

void RBD_Capacitance::update() {
  if(_sampling) {
    _takeSample();
  }
}

bool RBD_Capacitance::isFinished() {
  return _doneSampling();
}

unsigned long RBD_Capacitance::getValue() {
  return _getAverage();
}


// private

void RBD_Capacitance::_startSampling() {
  _sampling = true; // take many readings
  _startReading();  // take one reading
}

void RBD_Capacitance::_startReading() {
  _reading = true;
}

bool RBD_Capacitance::_doneSampling() {
  return !_sampling;
}

bool RBD_Capacitance::_doneReading() {
  return !_reading;
}

unsigned long RBD_Capacitance::_getReading() {
  return _total_reading; // current reading
}

unsigned long RBD_Capacitance::_getAverage() {
  return _total_average; // average of many readings
}

void RBD_Capacitance::_takeSample() {
  // keep reading
  _takeReading();

  // when a single reading has been collected
  if(_doneReading()) {
    // increment the sample count
    _sample_count++;
    // sum the reading
    _sample_sum += _getReading();

    // check if we can take another reading for this sample
    if(_sample_count < _sample_size) {
      // restart the reading process again
      _startReading();
    }
    // no more readings for this sample
    else {
      // save a moving average
      _total_average = _sample_sum / _sample_size;
      // reset counter variables
      _sample_sum   = 0;
      _sample_count = 0;
      // stop sampling
      _sampling = false;
    }
  }
}

void RBD_Capacitance::_takeReading() {
  // only fire this once per reading
  if(!_charging) {
    // CHARGE
    // turn on the send pin
    digitalWrite(_send_pin, HIGH);
    // start counter
    _start = micros();
    // start charging the pin
    _charging = true;
  }

  // wait until the receive pin is charged
  if(bool(digitalRead(_receive_pin))) {
    // save the time in microseconds
    _total_reading = micros() - _start;

    // STOP
    // turn off the send pin
    digitalWrite(_send_pin, LOW);
    // stop charging the pin
    _charging = false;
    // stop taking a reading
    _reading = false;

    // DISCHARGE
    // set receive pin to output
    pinMode(_receive_pin, OUTPUT);
    // set receive pin to low (ground)
    digitalWrite(_receive_pin, LOW);

    // RESET
    // set the receive pin back up to input
    pinMode(_receive_pin, INPUT);
  }
}