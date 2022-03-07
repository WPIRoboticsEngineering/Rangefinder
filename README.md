# Rangefinder
Library for the ultrasonic rangefinder HC-SR04.

## Installing the library (PlatformIO)
Add the following lines of code to your platformio.ini file:
~~~{.cpp}
lib_deps = 
     https://github.com/WPIRoboticsEngineering/Rangefinder
~~~

You are done.

## Classes and functions
The main classes and functions provided by the library are listed below:
* Rangefinder(uint8_t echo, uint8_t trig);
* void init(void);
* uint8_t checkPingTimer(void);
* uint16_t checkEcho(void);
* float getDistance(void);
* void ISR_echo(void);

## Datasheet
The datasheet of the HC-SR04 rangefinder can be found [here](https://media.digikey.com/pdf/Data%20Sheets/Adafruit%20PDFs/3942_Web.pdf).