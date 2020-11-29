#include <AsyncDelay.h>

AsyncDelay oneShot;
bool messagePrinted = false;

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Starting one-shot timer");
  oneShot.start(5000, AsyncDelay::MILLIS);
}


void loop(void)
{
  if (!messagePrinted && oneShot.isExpired()) {
    Serial.print("The timer was started ");
    Serial.print(oneShot.getDelay());
    if (oneShot.getUnit() == AsyncDelay::MILLIS)
      Serial.println(" ms ago");
    else
      Serial.println(" us ago");
    messagePrinted = true; // Print the message just once
    oneShot = AsyncDelay();
  }
}
