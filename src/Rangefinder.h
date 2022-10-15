#pragma once

#include <Arduino.h>

/** \class Rangefinder 
 * \brief Virtual base class to manage ultrasonic rangefinders. 
 * 
 * */
class Rangefinder 
{
protected:
    // // for keeping track of ping intervals
    // uint32_t lastReading = 0;

    // // we set the pingInterval to 10 ms, but it won't actually ping that fast
    // // since it _only_ pings if the ECHO pin is low -- that is, it will ping
    // // in 10 ms or when the last echo is done, whichever is _longer_ 
    // uint32_t readingInterval = 10;    

    // // holds the last recorded distance
    // float distance = 999;

    // // checks to see if it's time to take a reading
    // bool checkReadingTimer(void);

    // uint8_t ctrlPing = -1;

public:
    Rangefinder(void) {}

    // must call init() in your setup() function
    //virtual void init(void) = 0;

    /** \brief Commands a ping
     * */
    virtual void commandPing(void) = 0;

    /** \brief Returns true when there is a new echo and false otherwise.
     * The last recorded distance will be stored in distance.
     * */
    virtual bool getDistance(float& distance) = 0;
};
