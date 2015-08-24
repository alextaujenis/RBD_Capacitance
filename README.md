#Arduino Capacitance Library
You can detect human presence and touch from behind several millimeters of material, or detect changes in water levels from the outside of a plastic container. This library is meant to help **determine relative capacitance** and not for calculating exact capacitance.

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

##Sensitivity
Sensitivity is how far away the sensor can detect things.

* Increase sensitivity by **either** adding more resistors in series up to 20Meg or 30Meg or more, **or** increase the surface area (size) of the piece of aluminum used as the sensor

* Decrease sensitivity **either** by lowering the amount of resitance (use only 1Meg or less), **or** decrease the surface area (size) of the piece of aluminum used as the sensor

##Accuracy
Accuracy is how wildly the sensor readings fluctuate. This library helps adjust the accuracy by taking a moving average of many readings.

* Increase the [setSampleSize(1000)](#setsamplesizesize) value for more accurate readings that do not fluctuate so quickly
* Lower the [setSampleSize(10)](#setsamplesizesize) value for less accurate readings and to see numbers jump all over the place

You can get **very** accurate readings by increasing the [setSampleSize(5000)](#setsamplesizesize) to whatever you want, and this will not impact the Arduino real-time loop. It may take a bit longer to [getValue()](#getvalue) but the readings and moving average are all calculated in a fast non-blocking manner.

#Documentation
##Public Methods

* [constructor(send\_pin, receive\_pin)](#constructorsend_pin-receive_pin)
* [setSampleSize(size)](#setsamplesizesize)
* [start()](#start)
* [update()](#update)
* [isFinished()](#isfinished)
* [getValue()](#getvalue)

##constructor(send\_pin, receive\_pin)
Pass in integers for the send and receive pins to create a new instance of this class.

    Capacitance cap_sensor(1,0);

##setSampleSize(size)
Pass in an integer for the size to change the number of readings used for the moving average.

* **Increase Accuracy** by making this number larger setSampleSize(1000)
* **Decrease Accuracy** by making this number smaller setSampleSize(10)
* **Default Value** is setSampleSize(100)

Example:

    cap_sensor.setSampleSize(250);

##start()
Begin taking many readings.

    cap_sensor.start();

##update()
Keep processing the readings and move this library along in real-time.

    cap_sensor.update();

##isFinished()
Returns true if all readings have been taken and a moving average [getValue()](#getvalue) is ready.

    cap_sensor.isFinished();

##getValue()
Returns an unsigned long of the moving average value (microseconds to charge the pin) for the capacitance reading.

    cap_sensor.getValue();

#License
This code is available under the [MIT License](http://opensource.org/licenses/mit-license.php).