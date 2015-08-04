#include <Capacitance.h>

#define BAUD        115200
#define SEND_PIN    1 // tx
#define RECEIVE_PIN 0 // rx
#define SAMPLE_SIZE 300

int count = 0;
unsigned long total = 0;

Capacitance cap_sensor(SEND_PIN, RECEIVE_PIN);

void setup() {
  Serial.begin(BAUD);
  // kick off the reading process
  cap_sensor.startReading();
}

void loop() {
  // keep moving in real-time
  cap_sensor.update();

  // when a single reading has been collected
  if(cap_sensor.doneReading()) {

    // check if we have taken enough readings
    if(count < SAMPLE_SIZE) {
      // sum the reading
      total += cap_sensor.getValue();
      count++;
    }
    else {
      // print the moving average
      Serial.println(total / SAMPLE_SIZE);
      // reset counter variables
      total = 0;
      count = 0;
    }

    // restart the reading process
    cap_sensor.startReading();
  }
}
