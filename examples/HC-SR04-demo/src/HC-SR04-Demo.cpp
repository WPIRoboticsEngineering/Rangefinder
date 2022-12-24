#include <Arduino.h>
#include <HC-SR04.h>
#include <Romi32U4Buttons.h>

Romi32U4ButtonA buttonA;

void ISR_HC_0(void);
HC_SR04 hc_0(0, A2);

void ISR_HC_0(void)
{
  hc_0.ISR_echo();
}

void ISR_HC_1(void);
HC_SR04 hc_1(1, 4);

void ISR_HC_1(void)
{
  hc_1.ISR_echo();
}

void setup() 
{
  Serial.begin(115200);
  delay(100);
  while(!Serial) {}

  Serial.print("Welcome!\n");
  
  hc_0.init(ISR_HC_0);
  hc_1.init(ISR_HC_1);
}

void loop()
{
  float distance = 0;
  if(hc_0.getDistance(distance))
  {
    Serial.print(millis());
    Serial.print("\tHC0\t");
    Serial.println(distance);
  }

  if(hc_1.getDistance(distance))
  {
    Serial.print(millis());
    Serial.print("\tHC1\t");
    Serial.println(distance);
  }

  if(buttonA.getSingleDebouncedPress()) 
    {
      //Serial.println("Just one ping."); 
      hc_0.commandPing();
      hc_1.commandPing();
    }
}
