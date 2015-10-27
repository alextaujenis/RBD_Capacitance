// Arduino RBD Capacitance Library v1.0.3 Example - Continuously print the capacitance value.
// https://github.com/alextaujenis/RBD_Capacitance
// Copyright 2015 Alex Taujenis
// MIT License

#include <RBD_Capacitance.h> // https://github.com/alextaujenis/RBD_Capacitance

RBD::Capacitance cap_sensor(1, 0); // send, receive

void setup() {
  Serial.begin(115200);
}

void loop() {
  cap_sensor.update();

  if(cap_sensor.onChange()) {
    Serial.println(cap_sensor.getValue());
  }
}