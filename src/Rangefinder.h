#pragma once

#include <Arduino.h>

/** \class Rangefinder 
 * \brief Base class to manage the HC-SR04 distance sensors. 
 * Manages a timer and general interface. Derived classes specialize for various sensors.
 * */
class Rangefinder 
{
protected:
    // for keeping track of ping intervals
    uint32_t lastReading = 0;     

    // we set the pingInterval to 10 ms, but it won't actually ping that fast
    // since it _only_ pings if the ECHO pin is low -- that is, it will ping
    // in 10 ms or when the last echo is done, whichever is _longer_ 
    uint32_t readingInterval = 10;    

    // holds the last recorded distance
    float distance = 999;

    // checks to see if it's time to take a reading
    bool checkReadingTimer(void);

public:
    Rangefinder(void) {}

    // must call init() in your setup() function
    virtual void init(void) {}

    /** \brief Returns true when there is a new echo and false otherwise.
     * The last recorded distance will be stored in distance.
     * */
    virtual bool getDistance(float& distance) = 0;
};
