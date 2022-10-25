#include <HC-SR04.h>
#include <PCint.h>

#define ECHO_RECD   0x02

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
    attachInterrupt(digitalPinToInterrupt(echoPin), ::ISR_HC_SR04, CHANGE);
  }
  else if(digitalPinToPCInterrupt(echoPin) != NOT_AN_INTERRUPT)
  {
    Serial.println("Attaching rangefinder PC_ISR");
    attachPCInt(digitalPinToPCInterrupt(echoPin), ::ISR_HC_SR04);
  }
  else
  {
    Serial.println("Not a rangefinder interrupt pin!");
  }

  //control pin for commanding pings must be an output
  pinMode(trigPin, OUTPUT);
}

/**
 * \brief sendPingIfReady() checks to see if it's time to send a new ping.
 * 
 * You can make the pingInterval arbitrarily small, since it won't send a ping
 * if the ECHO pin is HIGH.
 * 
 * getDistance() calls this function, so you don't need to call this function manually.
 */
void HC_SR04::commandPing(void)
{
    //check if echo has been received -- only send if ECHO is LOW
    if(!digitalRead(echoPin))
    {
        //disable interrupts while we adjust the ISR variables
        //would be better to just disable this one interrupt, but it would be messy
        cli();
        pulseEnd = pulseStart = 0;

        //clear out any leftover states
        state = 0;
        sei();

        // toggle the trigger pin to send a chirp
        digitalWrite(trigPin, HIGH); //commands a ping; leave high for the duration
        delayMicroseconds(30); //datasheet says hold HIGH for >20us; we'll use 30 to be 'safe'
        digitalWrite(trigPin, LOW); //unclear if pin has to stay HIGH
    }
}

bool HC_SR04::getDistance(float& distance)
{
    bool retVal = false;

    uint16_t echoLength = 0;
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
