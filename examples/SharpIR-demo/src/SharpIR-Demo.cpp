#include <Arduino.h>
#include <PCint.h>
#include <Sharp-IR.h>

SharpIR sharpIR(A0);

void setup() 
{
  Serial.begin(115200);
  Serial.print("Welcome!\n");

  sharpIR.init();
}

void loop()
{
  float distance = 0;
  if(sharpIR.getDistance(distance))
  {
    Serial.println(distance);
  }
}
