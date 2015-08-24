#Arduino Capacitance Library
This library is meant to help **determine change in capacitance** and not for calculating exact capacitance. You can detect human presence and touch from behind several millimeters of material, or detect changes in water levels from the outside of a plastic container.

This real-time library requires that you manage the flow of your program without delay() or interrupts. Check out this [Arduino Timer Library](https://github.com/alextaujenis/Timer) if you are managing millis() by hand.

##Example Setup
0. Bridge a 10Meg Ohm resistor across the send (tx 1) and receive (rx 0) pins
0. Run a length of wire from the receive (rx 0) pin to a strip of aluminum foil
0. Cover the foil with plastic, paper, wood, clay, or anything non-conductive
0. Load up the example sketch and open a serial connection at 115200 baud
0. Touch or move your hand by the sensor

###[example.ino](https://github.com/alextaujenis/Capacitance/blob/master/example/example.ino)

    #include <Capacitance.h>

    #define BAUD        115200
    #define SEND_PIN    1 // tx
    #define RECEIVE_PIN 0 // rx

    Capacitance cap_sensor(SEND_PIN, RECEIVE_PIN);

    void setup() {
      Serial.begin(BAUD);
      cap_sensor.setSampleSize(100); // default
      cap_sensor.start();
    }

    void loop() {
      cap_sensor.update();

      if(cap_sensor.isFinished()) {
        Serial.println(cap_sensor.getValue());
        cap_sensor.start();
      }
    }

#Sensitivity
Sensitivity is how far away the sensor can detect things.

* Increase sensitivity by **either** adding more resistors in series up to 20Meg or 30Meg or more, **or** increase the surface area (size) of the piece of aluminum used as the sensor

* Decrease sensitivity **either** by lowering the amount of resitance (use only 1Meg or less), **or** decrease the surface area (size) of the piece of aluminum used as the sensor

#Accuracy
Accuracy is how wildly the sensor readings fluctuate. This library helps adjust the accuracy by taking a moving average of many readings.

* Increase the [setSampleSize(1000)](https://github.com/alextaujenis/Capacitance#setsamplesizesize) value for more accurate readings that do not fluctuate so quickly
* Lower the [setSampleSize(10)](https://github.com/alextaujenis/Capacitance#setsamplesizesize) value for less accurate readings and to see numbers jump all over the place

You can get **very** accurate readings by increasing the [setSampleSize(5000)](https://github.com/alextaujenis/Capacitance#setsamplesizesize) to whatever you want, and this will not impact the Arduino real-time loop. It may take a bit longer to [getValue()](https://github.com/alextaujenis/Capacitance#getvalue) but the readings and moving average are all calculated in a fast non-blocking manner.

#Documentation
##Public Methods

* [constructor(send\_pin, receive\_pin)](https://github.com/alextaujenis/Capacitance#constructorsend_pin-receive_pin)
* [setSampleSize(size)](https://github.com/alextaujenis/Capacitance#setsamplesizesize)
* [start()](https://github.com/alextaujenis/Capacitance#start)
* [update()](https://github.com/alextaujenis/Capacitance#update)
* [isFinished()](https://github.com/alextaujenis/Capacitance#isfinished)
* [getValue()](https://github.com/alextaujenis/Capacitance#getvalue)

##constructor(send\_pin, receive\_pin)
Create a new capacitance instance and pass in the send and receive pins.

##setSampleSize(size)
Change the number of readings used for the moving average in order to control accuracy.

* **Increase Accuracy** by making this number larger (example 1000).
* **Decrease Accuracy** by making this number smaller (example 10).
* **Default value is 100.**

##start()
Begin taking many readings.

##update()
Keep processing the readings and move this library along in real-time.

##isFinished()
All readings have been taken and a moving average [getValue()](https://github.com/alextaujenis/Capacitance#getvalue) is ready.

##getValue()
The moving average value of all capacitance readings.

#License
This code is available under the [MIT License](http://opensource.org/licenses/mit-license.php).