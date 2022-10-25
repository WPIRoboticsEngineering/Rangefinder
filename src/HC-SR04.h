#pragma once

#include <Arduino.h>
#include <Rangefinder.h>

/** \class HC_SR04 
 * \brief A class to manage the HC-SR04 ultrasonic rangefinder. 
 * 
 * Uses a TRIG and ECHO pin to send chirps and detect round trip time.
 * 
 * The object rangefinder is declared extern to work with the ISRs, which 
 * means you must define your object with the same name:
 * 
 * Rangefinder rangefinder(<echo>, <trigger>);
 * */
class HC_SR04 : public Rangefinder 
{
protected:
    volatile uint8_t state = 0;

    uint8_t echoPin = -1;
    uint8_t trigPin = -1;

    // for keeping track of echo duration
    volatile uint32_t pulseStart = 0;
    volatile uint32_t pulseEnd = 0;

public:
    HC_SR04(uint8_t echo, uint8_t trig);

    // must call init() to set up pins and interrupts
    void init(void);

//protected:
    // checks to see if it's time to emit a ping
    void commandPing(void);

public:
    /** \brief Returns true upon receiving a new echo and false otherwise.
     * The last recorded distance will be stored in distance.
     * */
    bool getDistance(float& distance);

    // ISR for the echo pin
    void ISR_echo(void);
};

extern HC_SR04 hc_sr04;