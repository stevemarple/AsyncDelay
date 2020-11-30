#ifndef ASYNCDELAY_H
#define ASYNCDELAY_H

#include <Arduino.h>

#define ASYNCDELAY_VERSION "1.1.2"

/**
 * @file AsyncDelay.h
 */


/**
 * @class AsyncDelay
 * @brief A timer implementation safe from the effects of rollover.
 * @details The AsyncDelay class conveniently encapsulates the
 *  behaviour described at
 *  http://arduino.cc/playground/Code/TimingRollover
 *
 *  @author Steve Marple
 */
class AsyncDelay {
  public:

    /**
     * @brief The unit used for the delay
     */
    enum units_t {
      /**
       * @brief Microseconds
       */
      MICROS,
      /**
       * @brief Milliseconds
       */
      MILLIS,
    };


    /**
     * @brief Default AsyncDelay constructor
     * @details Initializes the delay to zero. 
     * The timer will always be expired until `start()` is called.
     */
    inline AsyncDelay(void) : _delay(0), _unit(MILLIS) {
      expires = millis() + _delay;
    }

    /**
     * @brief Construct a new Async Delay object
     *
     * @param delay The duration the timer should wait for
     * @param unit The time unit for the delay
     */
    inline AsyncDelay(unsigned long delay, units_t unit)
      : _delay(delay), _unit(unit) {
      if (_unit == MICROS)
        expires = micros() + _delay;
      else
        expires = millis() + _delay;
    }

    /**
     * @brief Test if the timer has expired
     *
     * @return true if the timer has expired, false if not
     */
    inline bool isExpired(void) const {
      if (_unit == MICROS)
        return (long(micros() - expires) >= 0);
      else
        return (long(millis() - expires) >= 0);
    }

    /**
     * @brief Test if the timer has expired
     * @return true if the timer has expired, false if not
     */
    inline bool isExpired(void) const volatile {
      if (_unit == MICROS)
        return (long(micros() - expires) >= 0);
      else
        return (long(millis() - expires) >= 0);
    }

    /**
     * @brief Start a timer
     *
     * @param delay The duration the timer should wait for
     * @param unit The time unit for the delay
     */
    inline void start(unsigned long delay, units_t unit) {
      _delay = delay;
      _unit = unit;
      if (_unit == MICROS)
        expires = micros() + _delay;
      else
        expires = millis() + _delay;
    }

    /**
     * @brief Start a timer
     *
     * @param delay The duration the timer should wait for
     * @param unit The time unit for the delay
     */
    inline void start(unsigned long delay, units_t unit) volatile {
      _delay = delay;
      _unit = unit;
      if (_unit == MICROS)
        expires = micros() + _delay;
      else
        expires = millis() + _delay;
    }

    /**
     * @brief Start the timer from when it expired
     */
    inline void repeat(void) {
      expires += _delay;
    }

    /**
     * @brief Start the timer from when it expired
     */
    inline void repeat(void) volatile {
      expires += _delay;
    }

    /**
     * @brief Restart the timer from now
     */
    inline void restart(void) {
      if (_unit == MICROS)
        expires = micros() + _delay;
      else
        expires = millis() + _delay;
    }

    /**
     * @brief Restart the timer from now
     */
    inline void restart(void) volatile {
      if (_unit == MICROS)
        expires = micros() + _delay;
      else
        expires = millis() + _delay;
    }

    /**
     * @brief Force a timer to become expired
     */
    inline void expire(void) {
      if (_unit == MICROS)
        expires = micros();
      else
        expires = millis();
    }

    /**
     * @brief Force a timer to become expired
     */
    inline void expire(void) volatile {
      if (_unit == MICROS)
        expires = micros();
      else
        expires = millis();
    }

    /**
     * @brief Get the delay
     *
     * @return unsigned long The delay in whatever unit was set
     */
    inline unsigned long getDelay(void) const {
      return _delay;
    }

    /**
     * @brief Get the delay
     *
     * @return unsigned long The delay in whatever unit was set
     */
    inline unsigned long getDelay(void) const volatile {
      return _delay;
    }

    /**
     * @brief Get the units for the delay
     *
     * @return units_t The unit
     */
    inline units_t getUnit(void) const {
      return _unit;
    }

    /**
     * @brief Get the units for the delay
     *
     * @return units_t The unit
     */
    inline units_t getUnit(void) const volatile {
      return _unit;
    }

    /**
     * @brief Get the delay and unit
     *
     * @param delay Reference to where delay is to be saved
     * @param unit Reference to where unit is to be saved
     */
    inline void getDelay(unsigned long &delay, units_t &unit) const {
      delay = _delay;
      unit = _unit;
    }

    /**
     * @brief Get the delay and unit
     *
     * @param delay Reference to where delay is to be saved
     * @param unit Reference to where unit is to be saved
     */
    inline void getDelay(unsigned long &delay, units_t &unit) const volatile {
      delay = _delay;
      unit = _unit;
    }

    /**
     * @brief Get the time when the timer expires
     *
     * @return unsigned long Time in selected units
     */
    inline unsigned long getExpiry(void) const {
      return expires;
    }

    /**
     * @brief Get the time when the timer expires
     *
     * @return unsigned long Time in seelcted units
     */
    inline unsigned long getExpiry(void) const volatile {
      return expires;
    }

    /**
     * @brief Get the duration since the timer was started
     *
     * @return unsigned long Duration in selected units
     */
    inline unsigned long getDuration(void) const {
      if (_unit == MICROS)
        return micros() - expires;
      else
        return millis() - expires;
    }

    /**
     * @brief Get the duration since the timer was started
     *
     * @return unsigned long Duration in selected units
     */
    inline unsigned long getDuration(void) const volatile {
      if (_unit == MICROS)
        return micros() - expires;
      else
        return millis() - expires;
    }

  private:
    unsigned long _delay;
    unsigned long expires;
    units_t _unit;

};


#endif
