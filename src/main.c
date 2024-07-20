#include <stdio.h>
#include "Timer.h"

static unsigned long milliseconds = 0;
bool test = false;

void Blink(void *context)
{
  (void)context;
  test = !test;
  printf("%d\n", test);
}

static TimeSourceTicks_t ticks(I_TimeSource_t *instance)
{
  (void)instance;
  return (TimeSourceTicks_t)milliseconds;
}

static const I_TimeSource_Api_t api = {ticks};

I_TimeSource_t *TimeSource_Init(void)
{
  static I_TimeSource_t instance;
  instance.api = &api;

  return &instance;
}

int main(void)
{
  TimerGroup_t timerGroup;
  TimerGroup_Init(&timerGroup, TimeSource_Init());
  Timer_t timer;
  TimerGroup_StartPeriodic(&timerGroup, &timer, 5, Blink, NULL);

  while (1)
  {
    milliseconds++;
    TimerGroup_Run(&timerGroup);
  }

  return 0;
}