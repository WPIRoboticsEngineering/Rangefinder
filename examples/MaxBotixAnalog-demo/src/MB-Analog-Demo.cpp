#include <Arduino.h>
#include <MaxBotix.h>

MaxBotixAnalog mbAnalog(A0);

void setup() 
{
  Serial.begin(115200);
  Serial.print("Welcome!\n");

  mbAnalog.init();
}

void loop()
{
  float distance = 0;
  if(mbAnalog.getDistance(distance))
  {
    Serial.print(millis());
    Serial.print('\t');
    Serial.print(distance);
    Serial.print('\n');
  }
}
