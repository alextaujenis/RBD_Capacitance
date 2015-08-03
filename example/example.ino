#include <Capacitance.h>

#define BAUD        115200
#define SEND_PIN    1 // tx
#define RECEIVE_PIN 0 // rx9
#define SAMPLE_SIZE 300

int count = 0;
unsigned long total = 0;

Capacitance cap_sensor(SEND_PIN, RECEIVE_PIN);

void setup() {
  Serial.begin(BAUD);
  cap_sensor.getValue();
}

void loop() {
  cap_sensor.update();
  if(cap_sensor.isFinished()) {
    if(count < SAMPLE_SIZE) {
      total += cap_sensor.total();
      count++;
    }
    else {
      Serial.println(total / SAMPLE_SIZE);
      total = 0;
      count = 0;
    }
    cap_sensor.getValue();
  }
}