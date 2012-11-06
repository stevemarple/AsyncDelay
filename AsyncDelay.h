#ifndef ASYNCDELAY_H
#define ASYNCDELAY_H

/*
 * A timer implementation for the Arduino which is safe from the
 * effects of rollover. See
 * http://arduino.cc/playground/Code/TimingRollover for details. This
 * class conveniently encapsulates that behaviour.
 */

#include <Arduino.h>

class AsyncDelay {
public:
  enum units_t {
    MICROS,
    MILLIS,
  };

  // Have default delay to be zero so that timer is already expired
  inline AsyncDelay(void) : delay(0), unit(MILLIS) {
    expires = millis() + delay;
  }
  
  inline AsyncDelay(unsigned long d, units_t u)
    : delay(d), unit(u) {
    if (unit == MICROS)
      expires = micros() + delay;
    else
      expires = millis() + delay;
  }
  
  inline bool isExpired(void) const {
    if (unit == MICROS)
      return (long(micros() - expires) >= 0);
    else
      return (long(millis() - expires) >= 0);
  }

  inline void start(unsigned long d, units_t u) {
    delay = d;
    unit = u;
    if (unit == MICROS)
      expires = micros() + delay;
    else
      expires = millis() + delay;
  }

  // Restart the delay from when it expired (not now)
  inline void repeat(void) {
    expires += delay;
  }

  // Force a delay to be expired
  inline void expire(void) {
    if (unit == MICROS)
      expires = micros();
    else
      expires = millis();   
  }

  inline void getDelay(unsigned long &d, units_t &u) {
    d = delay;
    u = unit;
  }
  
private:
  unsigned long delay;
  unsigned long expires;
  units_t unit;
  
};



#endif
