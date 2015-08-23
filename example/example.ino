#include <Capacitance.h>

#define BAUD        115200
#define SEND_PIN    1 // tx
#define RECEIVE_PIN 0 // rx

Capacitance cap_sensor(SEND_PIN, RECEIVE_PIN);

void setup() {
  Serial.begin(BAUD);
  // take 100 readings and average them as one
  cap_sensor.setSampleSize(100); // default
  // start taking readings
  cap_sensor.start();
}

void loop() {
  // keep moving in real-time
  cap_sensor.update();

  // if finished taking a reading
  if(cap_sensor.isFinished()) {
    // print the reading value
    Serial.println(cap_sensor.value());
    // start taking another reading
    cap_sensor.start();
  }
}
