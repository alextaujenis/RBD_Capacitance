#Arduino Capacitance Library
A library for measuring capacitance. Detect human presence and touch from behind several millimeters of material. Detect changes in water levels from outside a plastic container.

This library is meant to **help determine change in capacitance** for the reasons mentioned above, and **not for calculating exact capacitance**.

*Also, this is real-time because it **doesn't use delay or interrupts** to halt program flow. However, it does cycle through a _while loop_ for a few **microseconds** to take a reading.

##Wiring Setup
Bridge a 10MEG ohm resistor across the send and receive pins. Run a length of wire from the receive pin to a strip of aluminum foil. Cover the foil with plastic, paper, wood, or clay... anything non-conductive. Keep the thickness of the non-conductive cover to an inch or less (yeah, it's sensitive).

#Documentation
##Public Methods

* [constructor(send\_pin, receive\_pin)]()
* [getValue()]()

##constructor(send\_pin, receive\_pin)
Create a new capacitance instance and pass in the send and receive pins.