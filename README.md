#Arduino Capacitance Library
Detect human presence and touch from behind several millimeters of material, or detect changes in water levels from the outside of a plastic container. This library is meant to help determine change in relative capacitance for the reasons above, and not for calculating exact capacitance.

Relative capacitance is found by measuring how long it takes for an Arduino send-pin to charge a receive-pin to HIGH (in microseconds). Changes in the electrical field around a sensor connected to the receive pin (such as a human passing by, or water filling up, or a motor turning on) have a measurable impact on the amount of time it takes to charge the receive pin.

Many of these charge and discharge readings are taken, then averaged within the library to reduce variability and give a more clear answer of what the sensor is reading. This is done in real-time without delay so it only has a small impact on the main loop() performance. See the [Example](#example-setup) below for help wiring and programming the Arduino with this library.

##Real-Time Library

This real-time library requires that you manage the flow of your program without delay() or interrupts. Check out this [Arduino Timer Library](https://github.com/alextaujenis/RBD_Timer) if you are managing millis() by hand.

##Example Setup

0. Bridge a 10Meg Ohm resistor across the Arduino send (tx 1) and receive (rx 0) pins
0. Run a length of wire from the receive (rx 0) pin to a strip of aluminum foil
0. Cover the foil with plastic, paper, wood, clay, or anything non-conductive
0. Load up the example sketch and open a serial connection at 115200 baud
0. Touch or move your hand by the sensor

**Example Sketch**:

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

##Sensitivity
Sensitivity is how far away the sensor can detect things, or how much resolution you have to recognize change in the sensor readings.

* Increase Sensitivity by **either** adding more resistors in series (20Meg, 30Meg, or more), or increase the surface area (size) of the piece of aluminum used as the sensor.

* Decrease Sensitivity by **either** lowering the amount of resitance (use only 1Meg or less), or decrease the surface area (size) of the piece of aluminum used as the sensor.

##Variability
Variability is how wildly the sensor readings fluctuate. This library helps adjust the variability by taking a moving average of many readings over time. This is done without delay so it has little impact on the main loop() performance.

* Less Variable readings that don't fluctuate so quickly can be achieved by increasing the sample size: [setSampleSize(1000)](#setsamplesizesize).
* More Variable readings that fluctuate quickly can be achieved by decreasing the sample size: [setSampleSize(10)](#setsamplesizesize).

You can get **very** accurate readings by increasing the [setSampleSize(5000)](#setsamplesizesize) to whatever you want, and this will not impact the Arduino real-time loop. It may take a bit longer to [getValue()](#getvalue) but the readings and moving average are all calculated in a fast non-blocking manner.

#Documentation
##Public Methods

* [constructor(send\_pin, receive\_pin)](#constructorsend_pin-receive_pin)
* [update()](#update)
* [setSampleSize(size)](#setsamplesizesize)
* [start()](#start)
* [isFinished()](#isfinished)
* [getValue()](#getvalue)
* [onChange()](#onchange)

##constructor(send\_pin, receive\_pin)
Create a new capacitance sensor and pass in the Arduino pin numbers for the send and receive pins.

    RBD::Capacitance cap_sensor(1,0);

    void setup() {
      ...
    }

##update()
This must be call continuously from within the loop() to move the library along in real-time.

    void loop() {
      cap_sensor.update();
    }

##setSampleSize(size)
Pass in an integer to change the number of readings taken to calculate a moving average [getValue()](#getvalue). This can be called inside of setup() or also safely at runtime inside of loop().

* **Decrease Variation** in readings by making this number larger: 1000
* **Increase Variation** in readings by making this number smaller: 10
* **Default Value**: 100

Example:

    void setup() {
      cap_sensor.setSampleSize(1000);
    }

##start()
Begin taking many readings and start adding up the moving average for [getValue()](#getvalue).

    void setup() {
      cap_sensor.start();
    }

    void loop() {
      cap_sensor.update();
    }


##isFinished()
Returns true if all readings have been taken and a moving average [getValue()](#getvalue) is ready. You must first call [start()](#start) to begin the sampling process.

    void setup() {
      cap_sensor.start();
    }

    void loop() {
      cap_sensor.update();

      if(cap_sensor.isFinished()) {
        ...
      }
    }
##getValue()
Returns an unsigned long of the moving average value for the capacitance reading (microseconds taken to charge the pin). This will only return a value after calling [start()](#start) and waiting until [isFinished()](#isfinished) has returned true.

    void setup() {
      cap_sensor.start();
    }

    void loop() {
      cap_sensor.update();

      if(cap_sensor.isFinished()) {
        Serial.println(cap_sensor.getValue());
      }
    }

##onChange()
This method will fire a single event and start taking another sensor reading each time the [getValue()](#getvalue) changes, mimicking the same process of creating a loop by calling [start()](#start) and [isFinished()](#isfinished) together, but with a simple syntax and a tighter time loop.

    void loop() {
      cap_sensor.update();

      if(cap_sensor.onChange()) {
        // code block runs once per change event
        Serial.println(cap_sensor.getValue());
      }
    }

#License
This code is available under the [MIT License](http://opensource.org/licenses/mit-license.php).