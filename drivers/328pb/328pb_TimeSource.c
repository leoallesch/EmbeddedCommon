#include "328pb_TimeSource.h"

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned long milliseconds = 0;

static void Timer1_Init()
{
  // Set Timer1 to CTC mode
  TCCR1A = 0;
  TCCR1B = (1 << WGM12); // CTC mode
  // Set the compare value for 1 ms interrupt
  OCR1A = 249; // (16e6 / (64 * 1000)) - 1 = 249
  // Enable Timer1 Compare Match A interrupt
  TIMSK1 = (1 << OCIE1A);

  sei();

  // Start Timer1 with prescaler 64
  TCCR1B |= (1 << CS11) | (1 << CS10);
}

ISR(TIMER1_COMPA_vect)
{
  milliseconds++;
}

static unsigned long GetMs()
{
  unsigned long ms;
  uint8_t oldSREG = SREG; // Save the current state of the Status Register
  cli();                  // Disable interrupts
  ms = milliseconds;      // Read the milliseconds counter
  SREG = oldSREG;         // Restore the previous state of the Status Register
  sei();
  return ms;
}

static TimeSourceTicks_t ticks(I_TimeSource_t *instance)
{
  return (TimeSourceTicks_t)GetMs();
}

static const I_TimeSource_Api_t api = {ticks};

I_TimeSource_t *TimeSource_Init(void)
{
  static I_TimeSource_t instance;
  instance.api = &api;

  Timer1_Init();

  return &instance;
}