// Arduino RBD_Capacitance Library v1.0.0 Example  - Continuously print a capacitance value
// Copyright 2015 Alex Taujenis
// MIT License

#include <RBD_Capacitance.h>

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