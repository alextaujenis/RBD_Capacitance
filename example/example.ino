#include <Capacitance.h>

#define BAUD        115200
#define SEND_PIN    1 // tx
#define RECEIVE_PIN 0 // rx

Capacitance cap_sensor(SEND_PIN, RECEIVE_PIN);

void setup() {
  Serial.begin(BAUD);
  cap_sensor.startCycling();
}

void loop() {
  cap_sensor.update();
  if(cap_sensor.doneCycling()) {
    Serial.println(cap_sensor.getAverage());
    cap_sensor.startCycling();
  }
}
