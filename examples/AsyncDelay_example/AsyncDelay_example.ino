#include <AsyncDelay.h>

AsyncDelay delay_3s;
AsyncDelay delay_6s;

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Starting timers");

  // Start counting
  delay_3s.start(3000, AsyncDelay::MILLIS);
  delay_6s.start(6000, AsyncDelay::MILLIS);
}

void loop(void)
{
  if (delay_3s.isExpired()) {
    Serial.print("3s delay millis=");
    Serial.println(millis());
    delay_3s.repeat(); // Count from when the delay expired, not now
  }

  if (delay_6s.isExpired()) {
    Serial.print("     6s delay millis=");
    Serial.println(millis());
    delay_6s.repeat();
  }
  
}
