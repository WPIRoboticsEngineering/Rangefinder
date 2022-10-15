#include "MaxBotix.h"

#define ECHO_PIN    2
#define TRIG_PIN    -1

template<uint8_t pin> void MB_ISR(void)
{
    MaxBotixT<pin>::mbISR();
}

void MaxBotix::init(void)
{
    if(triggerPin != -1) // Arduino will ignore if it's -1, but good practice to check
    {
        //control pin for commanding pings
        pinMode(triggerPin, OUTPUT);
    }
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

bool MaxBotixAnalog::getDistance(float& distance)
{
    bool newReading = false;
    if(millis() - lastPing >= ADC_INTERVAL)
    {
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
