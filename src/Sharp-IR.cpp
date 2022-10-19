#include <Sharp-IR.h>

const uint32_t ADC_INTERVAL = 40;

bool SharpIR::getDistance(float& distance)
{
    bool newReading = false;
    if(millis() - lastReading >= ADC_INTERVAL)
    {
        uint16_t adcResult = analogRead(adcPin);
        distance = adcResult; //TODO

        newReading = true;
    }

    return newReading;
}
