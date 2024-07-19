#ifndef TIMER_H
#define TIMER_H

#include "../LinkedList/LinkedList.h"
#include "I_TimeSource.h"

typedef uint32_t Ticks_t;

struct TimerModule_t;

typedef void (*TimerCallback_t)(void *context);

typedef struct
{
  LinkedListNode_t node;
  TimerCallback_t callback;
  void *context;
  Ticks_t startTicks;
  Ticks_t endTicks;
  bool periodic;
  bool expired;
  bool paused;
} Timer_t;

typedef struct
{
  I_TimeSource_t *timeSource;
  LinkedList_t timers;
  TimeSourceTicks_t previousTicks;
  TimeSourceTicks_t currentTicks;
} TimerModule_t;

void TimerModule_Init(TimerModule_t *instance, I_TimeSource_t *timeSource);

Ticks_t TimerModule_Run(TimerModule_t *instance);

Ticks_t TimerModule_TicksUntilNextReady(TimerModule_t *instance);

void Timer_StartOneShot(TimerModule_t *timerModule, Timer_t *timer, Ticks_t ticks, void *context, TimerCallback_t callback);

void Timer_StartPeriodic(TimerModule_t *timerModule, Timer_t *timer, Ticks_t ticks, void *context, TimerCallback_t callback);

void Timer_Stop(TimerModule_t *timerModule, Timer_t *timer);

bool Timer_IsRunning(TimerModule_t *timerModule, Timer_t *timer);

Ticks_t Timer_TicksRemaining(TimerModule_t *timerModule, Timer_t *timer);

#endif
