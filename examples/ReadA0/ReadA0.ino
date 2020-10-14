/*
 * Simple demonstration of AsyncDelay to read the A0 analogue input
 * every 50 ms. 
*/
#include <AsyncDelay.h>


AsyncDelay samplingInterval;

void setup(void)
{
  Serial.begin(115200);
  samplingInterval.start(50, AsyncDelay::MILLIS);
}


void loop(void)
{
  if (samplingInterval.isExpired()) {
    uint16_t count  = analogRead(A0);
    samplingInterval.repeat();
    Serial.println(count);
  }
}
