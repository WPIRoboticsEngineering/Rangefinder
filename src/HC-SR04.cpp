#include <HC-SR04.h>
#include <PCint.h>

#define ECHO_RECD   0x02

#define ECHO    0
#define TRIG    A2

HC_SR04 hc_sr04(ECHO, TRIG);

// ISR for the echo
void ISR_HC_SR04(void) {hc_sr04.ISR_echo();}

/** \brief Constructor.
 * 
 * @param echo The echo pin. Must be interrupt enabled. PCInts OK.
 * @param trig The trigger pin.
 * */
HC_SR04::HC_SR04(uint8_t echo, uint8_t trig) : Rangefinder()
{
    echoPin = echo;
    trigPin = trig;
}

// sets up the interface
void HC_SR04::init(void)
{
  // ensure ECHO pin is an input
  pinMode(echoPin, INPUT);

  // register the interrupt for the echo
  if(digitalPinToInterrupt(echoPin) != NOT_AN_INTERRUPT)
  {
    Serial.println("Attaching rangefinder ISR");
    attachInterrupt(digitalPinToInterrupt(echoPin), ISR_HC_SR04, CHANGE);
  }
  else if(digitalPinToPCInterrupt(echoPin) != NOT_AN_INTERRUPT)
  {
    Serial.println("Attaching rangefinder PC_ISR");
    attachPCInt(digitalPinToPCInterrupt(echoPin), ISR_HC_SR04);
  }
  else
  {
    Serial.println("Not a rangefinder interrupt pin!");
  }

  //control pin for commanding pings must be an output
  pinMode(trigPin, OUTPUT);
}

/**
 * \brief commandPing() sends a ping. It checks to see if the ECHO is LOW
 */
void HC_SR04::commandPing(void)
{
    uint32_t currTime = millis();

    // only ping if ECHO is LOW
    if(!digitalRead(echoPin))
    {
      // check that at least 5 ms has expired since the pin went LOW to let echoes die out
      if(currTime - lastPingCheck > 5)
      {
          lastPingCheck = currTime; // update lastPingCheck

          //disable interrupts while we adjust the ISR variables
          cli();
          pulseEnd = pulseStart = 0;

          //clear out any leftover states
          state = 0;
          sei();

          // toggle the trigger pin to send a chirp
          digitalWrite(trigPin, HIGH); //commands a ping; leave high for the duration
          delayMicroseconds(20); //datasheet says hold HIGH for >10us; we'll use 20 to be 'safe'
          digitalWrite(trigPin, LOW); //unclear if pin has to stay HIGH
      }
    }

    else lastPingCheck = currTime; // update lastPingCheck
}

bool HC_SR04::getDistance(float& distance)
{
    bool retVal = false;

    uint32_t echoLength = 0;
    cli();
    if(state & ECHO_RECD)
    {
        echoLength = pulseEnd - pulseStart;
        state &= ~ECHO_RECD;

        retVal = true;
    }
    sei();
    
    // nominal translation as given by the datasheet; adjust as needed
    distance = echoLength / 58.0;

    return retVal;
}

/** \brief ISR for the echo pin
 * 
 * Records both the start and stop (rise and fall) of the echo pin.
 * When the pin goes low, it sets a flag.
 * */
void HC_SR04::ISR_echo(void)
{
    if(digitalRead(echoPin))  //transitioned to HIGH
    {
        pulseStart = micros();
    }

    else                      //transitioned to LOW
    {
        pulseEnd = micros();
        state |= ECHO_RECD;
    } 
}
