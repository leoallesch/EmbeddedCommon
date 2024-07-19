#include "Timer.h"

void TimerModule_Init(TimerModule_t *instance, I_TimeSource_t *timeSource)
{
  instance->timeSource = timeSource;
  instance->previousTicks = TimeSource_Ticks(timeSource);
  LinkedList_Init(&instance->timers);
}

static void AddTimer(TimerModule_t *instance, Timer_t *timer)
{
  LinkedList_Remove(&instance->timers, &timer->node);

  timer->expired = false;

  LinkedList_PushFront(&instance->timers, &timer->node);
}

static Ticks_t PendingTicks(TimerModule_t *instance)
{
  return TimeSource_Ticks(instance->timeSource) - instance->previousTicks;
}

Ticks_t TimerModule_Run(TimerModule_t *instance)
{
  TimeSourceTicks_t currentTicks = TimeSource_Ticks(instance->timeSource);
  TimeSourceTicks_t deltaTicks = currentTicks - instance->previousTicks;
  instance->previousTicks = currentTicks;

  TimeSourceTicks_t lastTicks = instance->currentTicks;
  instance->currentTicks += deltaTicks;

  LinkedList_ForEach(&instance->timers, Timer_t, timer, {
    if (timer->expired)
    {
      continue;
    }

    Ticks_t remainingTicks = timer->endTicks - lastTicks;

    if (remainingTicks <= deltaTicks)
    {
      timer->expired = true;
    }
    else
    {
      break;
    }
  });

  LinkedList_ForEach(&instance->timers, Timer_t, timer, {
    if (timer->expired)
    {
      if (!timer->periodic)
      {
        LinkedList_Remove(&instance->timers, &timer->node);
      }

      timer->callback(timer->context);

      if (timer->periodic && Timer_IsRunning(instance, timer))
      {
        timer->endTicks = instance->currentTicks += timer->startTicks;
        AddTimer(instance, timer);
      }
    }
    break;
  });
  // return TimerModule_TicksUntilNextReady(instance);
  return 0;
}

Ticks_t TimerModule_TicksUntilNextReady(TimerModule_t *instance);

void Timer_StartOneShot(TimerModule_t *timerModule, Timer_t *timer, Ticks_t ticks, void *context, TimerCallback_t callback)
{
  timer->periodic = false;
  timer->callback = callback;
  timer->context = context;
  timer->startTicks = ticks;
  timer->endTicks = timerModule->currentTicks + ticks + PendingTicks(timerModule);

  AddTimer(timerModule, timer);
}

void Timer_StartPeriodic(TimerModule_t *timerModule, Timer_t *timer, Ticks_t ticks, void *context, TimerCallback_t callback)
{
  timer->periodic = true;
  timer->callback = callback;
  timer->context = context;
  timer->startTicks = ticks;
  timer->endTicks = timerModule->currentTicks + ticks + PendingTicks(timerModule);

  AddTimer(timerModule, timer);
}

void Timer_Stop(TimerModule_t *timerModule, Timer_t *timer)
{
  LinkedList_Remove(&timerModule->timers, &timer->node);
}

bool Timer_IsRunning(TimerModule_t *timerModule, Timer_t *timer)
{
  return LinkedList_Contains(&timerModule->timers, &timer->node);
}

Ticks_t Timer_TicksRemaining(TimerModule_t *timerModule, Timer_t *timer);