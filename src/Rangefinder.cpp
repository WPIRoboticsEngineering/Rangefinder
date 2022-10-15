#include <Rangefinder.h>

/**
 * \brief checkPingTimer() checks to see if it's time to send a new ping.
 * 
 * You can make the pingInterval arbitrarily small, since it won't send a ping
 * if the ECHO pin is HIGH.
 * 
 * getDistance() calls this function, so you don't need to call this function manually.
 */
// bool Rangefinder::checkReadingTimer(void)
// {
//     bool retVal = false;
//     // check if we're ready to ping
//     if(millis() - lastReading >= readingInterval)
//     {
//         lastReading = millis();  
//         retVal = true;
//     }

//     return retVal;
// }
