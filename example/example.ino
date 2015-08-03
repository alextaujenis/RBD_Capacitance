#include <Capacitance.h>

#define BAUD        115200
#define SEND_PIN    1
#define RECEIVE_PIN 0
#define SAMPLE_SIZE 275

int counter = 0;
unsigned long avg;

Capacitance cap_sensor(SEND_PIN, RECEIVE_PIN);

void setup() {
  Serial.begin(BAUD);
}

void loop() {
  if(counter < SAMPLE_SIZE) {
    avg += cap_sensor.getValue();
    counter++;
  }
  else {
    avg = avg / SAMPLE_SIZE;
    Serial.println(avg);
    avg     = 0;
    counter = 0;
  }
}