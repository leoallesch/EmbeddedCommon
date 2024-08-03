#ifndef TIMER_H
#define TIMER_H

#include "LinkedList.h"
#include "I_TimeSource.h"

#include <stdint.h>
#include <stdbool.h>

typedef uint32_t TimerTicks_t;

typedef void (*TimerCallback_t)(void *context);

typedef struct
{
  LinkedListNode_t node;
  TimerCallback_t callback;
  void *context;
  TimerTicks_t startTicks;
  TimerTicks_t expirationTicks;
  bool periodic;
  bool expired;
} Timer_t;

typedef struct TimerGroup_t
{
  I_TimeSource_t *timeSource;
  LinkedList_t timers;
  TimeSourceTicks_t lastTimeSourceTicks;
  TimerTicks_t currentTicks;
} TimerGroup_t;

void TimerGroup_Init(TimerGroup_t *self, I_TimeSource_t *timeSource);

TimerTicks_t TimerGroup_Run(TimerGroup_t *self);

TimerTicks_t TimerGroup_TicksUntilNextReady(TimerGroup_t *self);

void TimerGroup_StartOneShot(
    TimerGroup_t *self,
    Timer_t *timer,
    TimerTicks_t ticks,
    TimerCallback_t callback,
    void *context);

void TimerGroup_StartPeriodic(
    TimerGroup_t *self,
    Timer_t *timer,
    TimerTicks_t ticks,
    TimerCallback_t callback,
    void *context);

void TimerGroup_Stop(TimerGroup_t *self, Timer_t *timer);

bool TimerGroup_TimerIsRunning(TimerGroup_t *self, Timer_t *timer);

TimerTicks_t TimerGroup_RemainingTicks(TimerGroup_t *self, Timer_t *timer);

#endif