#include <Arduino.h>
#include <HC-SR04.h>
#include <Romi32U4Buttons.h>

Romi32U4ButtonA buttonA;

void setup() 
{
  Serial.begin(115200);
  Serial.print("Welcome!\n");
  
  hc_sr04.init();
}

void loop()
{
  float distance = 0;
  if(hc_sr04.getDistance(distance))
  {
    Serial.print(millis());
    Serial.print('\t');
    Serial.println(distance);
  }

  if(buttonA.isPressed()) hc_sr04.commandPing();
}
