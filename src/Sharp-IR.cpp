#include <Sharp-IR.h>

const uint32_t SHARP_IR_INTERVAL = 1000;

bool SharpIR::getDistance(float& distance)
{
    bool newReading = false;
    uint32_t currTime = millis();
    if(currTime - lastReading >= SHARP_IR_INTERVAL)
    {
        lastReading = currTime;

        uint16_t adcResult = analogRead(adcPin);
        distance = adcResult; //TODO
        float voltage = 5 * adcResult / 1024.;
        float inv = (voltage - 0.127) / 20.81;
        distance = 1.0 / inv;

        newReading = true;
    }

    return newReading;
}
