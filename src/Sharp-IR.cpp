#include <Sharp-IR.h>

const uint32_t SHARP_IR_INTERVAL = 40;

bool SharpIR::getDistance(float& distance)
{
    bool newReading = false;
    if(millis() - lastReading >= SHARP_IR_INTERVAL)
    {
        uint16_t adcResult = analogRead(adcPin);
        distance = adcResult; //TODO

        newReading = true;
    }

    return newReading;
}
