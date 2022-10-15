#ifndef __MAXBOTIX_H
#define __MAXBOTIX_H

/*
 * Datasheet: https://www.maxbotix.com/documents/LV-MaxSonar-EZ_Datasheet.pdf
 */

#include <Arduino.h>
#include <Rangefinder.h>

#define PING_SENT   0x01
#define ECHO_RECD   0x02

class MaxBotix : public Rangefinder
{
protected:
    uint32_t lastPing = 0;
    int triggerPin = -1;

public:
    MaxBotix(uint8_t trig = -1) : triggerPin(trig) {}

    void init(void);

    virtual void commandPing(void);
};

template<uint8_t p> void MB_ISR(void);

template<uint8_t pin> class MaxBotixT : public MaxBotix
{
private:
    volatile uint8_t state  = 0;

    volatile uint32_t pulseStart = 0;
    volatile uint32_t pulseEnd = 0;

public:
    MaxBotixT(uint8_t trig = -1) : MaxBotix(trig) {}

    void init(void)
    {
        MaxBotix::init();

        pinMode(pin, INPUT);
        attachInterrupt(digitalPinToInterrupt(pin), MB_ISR<pin>, CHANGE);
    }

    virtual bool getDistance(float& distance)
    {
        bool newReading = false;
        if(state & ECHO_RECD)
        {
            state &= ~ECHO_RECD;  //cli???
            uint16_t echoLength = pulseEnd - pulseStart;

            distance = echoLength;
            newReading = true;
        }

        return newReading;
    }

    void mbISR(void)
    {
        if(digitalRead(pin))  //transitioned to HIGH
        {
            pulseStart = micros();
        }

        else                        //transitioned to LOW
        {
            pulseEnd = micros();
            state |= ECHO_RECD;
        } 
    }

};

class MaxBotixAnalog : public MaxBotix
{
private:
    uint8_t adcPin = -1;
public:
    MaxBotixAnalog(uint8_t adc, uint8_t trig = -1) : MaxBotix(trig) {adcPin = adc;}
    virtual void init(void) {MaxBotix::init(); pinMode(adcPin, INPUT);}
    //void commandPing(void) {MaxBotix::commandPing();}
    bool getDistance(float& distance);
};

class MaxBotixSerial : public MaxBotix
{
private:
    String serialString;

public:
    MaxBotixSerial(uint8_t trig = -1) : MaxBotix(trig) {}

    void init(void) {MaxBotix::init(); Serial1.begin(9600);}

    bool getDistance(float& distance);
};

extern MaxBotixT<15> mb15;

#endif