#include <Sharp-IR.h>

const uint32_t SHARP_IR_INTERVAL = 50;

bool SharpIR::getDistance(float& distance)
{
    bool newReading = false;
    uint32_t currTime = millis();
    if(currTime - lastReading >= SHARP_IR_INTERVAL)
    {
        lastReading = currTime;

        uint16_t adcResult = analogRead(adcPin);
        Serial.print(adcResult);
        Serial.print('\t');
        distance = adcResult; //TODO
        float voltage = 5 * adcResult / 1024.;
        float inv = (voltage - 0.127) / 20.81; if(inv < 0.01) inv = 0.01;
        distance = 1.0 / inv;

#ifdef __SHARP_DEBUG__
        Serial.println(distance);
#endif

        newReading = true;
    }

    return newReading;
}
