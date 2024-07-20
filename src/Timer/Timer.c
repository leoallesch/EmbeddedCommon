#include "Timer.h"

static void AddTimer(TimerGroup_t *self, Timer_t *timer)
{
  LinkedList_Remove(&self->timers, &timer->node);
  timer->expired = false;
  LinkedList_PushFront(&self->timers, &timer->node);
}

static TimeSourceTicks_t PendingTicks(TimerGroup_t *self)
{
  return TimeSourceTicks(self->timeSource) + self->lastTimeSourceTicks;
}

void TimerGroup_Init(TimerGroup_t *self, I_TimeSource_t *timeSource)
{
  self->timeSource = timeSource;
  self->lastTimeSourceTicks = TimeSourceTicks(timeSource);
  LinkedList_Init(&self->timers);
}

void TimerGroup_Run(TimerGroup_t *self)
{
  TimeSourceTicks_t currentTimeSourceTicks = TimeSourceTicks(self->timeSource);
  TimeSourceTicks_t delta = currentTimeSourceTicks - self->lastTimeSourceTicks;

  TimerTicks_t lastTicks = self->currentTicks;
  self->lastTimeSourceTicks = currentTimeSourceTicks;
  self->currentTicks += delta;

  LinkedList_ForEach(&self->timers, Timer_t, timer, {
    if (timer->expired)
    {
      continue;
    }

    TimerTicks_t remainingTicks = timer->expirationTicks - lastTicks;

    if (remainingTicks <= delta)
    {
      timer->expired = true;
    }
    else
    {
      break;
    }
  });

  LinkedList_ForEach(&self->timers, Timer_t, timer, {
    if (timer->expired)
    {
      if (!timer->periodic)
      {
        LinkedList_Remove(&self->timers, &timer->node);
      }

      timer->callback(timer->context);

      if (timer->periodic && TimerGroup_TimerIsRunning(self, timer))
      {
        timer->expirationTicks = self->currentTicks + timer->startTicks;
        AddTimer(self, timer);
      }
    }
    break;
  });
}

void TimerGroup_StartOneShot(
    TimerGroup_t *self,
    Timer_t *timer,
    TimerTicks_t ticks,
    TimerCallback_t callback,
    void *context)
{
  timer->periodic = false;
  timer->callback = callback;
  timer->context = context;
  timer->startTicks = ticks;
  timer->expirationTicks = self->currentTicks + ticks + PendingTicks(self);
  AddTimer(self, timer);
}

void TimerGroup_StartPeriodic(
    TimerGroup_t *self,
    Timer_t *timer,
    TimerTicks_t ticks,
    TimerCallback_t callback,
    void *context)
{
  timer->periodic = true;
  timer->callback = callback;
  timer->context = context;
  timer->startTicks = ticks;
  timer->expirationTicks = self->currentTicks + ticks + PendingTicks(self);
  AddTimer(self, timer);
}

bool TimerGroup_TimerIsRunning(TimerGroup_t *self, Timer_t *timer)
{
  return LinkedList_Contains(&self->timers, &timer->node);
}