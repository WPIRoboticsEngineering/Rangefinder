#include "MaxBotix.h"

void MaxBotix::init(void)
{
    Serial.println("MaxBotix::init()");

    if(triggerPin != -1) // Arduino will ignore if it's -1, but good practice to check
    {
        //control pin for commanding pings
        pinMode(triggerPin, OUTPUT);
    }
    Serial.println("/MaxBotix::init()");
}

void MaxBotix::commandPing(void)
{
    if(triggerPin != -1)
    {
        // ... toggle the tigger
        digitalWrite(triggerPin, HIGH); //commands a ping; leave high for the duration
        delayMicroseconds(25); //datasheet says hold HIGH for >20us; we'll use 25 to be 'safe'
        digitalWrite(triggerPin, LOW); //unclear if pin has to stay HIGH

        lastPing = millis();
    }
}

const uint32_t ADC_INTERVAL = 40;

void MaxBotixPulse::init(void)
{
    Serial.println("MaxBotixT::init()");
    MaxBotix::init();

    pinMode(echoPin, INPUT);
    Serial.println("/MaxBotixT::init()");
}

bool MaxBotixPulse::getDistance(float& distance)
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

bool MaxBotixAnalog::getDistance(float& distance)
{
    bool newReading = false;
    uint32_t currTime = millis();
    if(currTime - lastPing >= ADC_INTERVAL)
    {
        lastPing = currTime;
        uint16_t adcResult = analogRead(adcPin);
        distance = adcResult; //TODO

        newReading = true;
    }

    return newReading;
}

bool MaxBotixSerial::getDistance(float& distance)
{
    bool newReading = false;
    while(Serial1.available())
    {
        char c = Serial1.read();

        if(c != 'R') serialString += c;
        if(c == 0xD) 
        {
            uint16_t result = serialString.toInt();
            serialString = "";
            distance = result;

            newReading = true;
        }
    }

  return newReading;
}
