#include <Arduino.h>
#include <MaxBotix.h>
#include <Romi32U4Buttons.h>

MaxBotixPulse mbPulse(2);

void MB_ISR(void)
{
  mbPulse.mbISR();
}

void setup() 
{
  Serial.begin(115200);
  Serial.print("Welcome!\n");
  
  mbPulse.init();
  attachInterrupt(digitalPinToInterrupt(1), MB_ISR, CHANGE);
}

void loop()
{
  float distance = 0;
  if(mbPulse.getDistance(distance))
  {
    Serial.println(distance);
  }
}
