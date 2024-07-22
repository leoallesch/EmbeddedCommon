#include "EventSubscription.h"

void EventSubscription_Init(EventSubscription_t *self, void *context, EventCallback_t callback)
{
  self->context = context;
  self->callback = callback;
}

void EventSubscription_Publish(EventSubscription_t *self, const void *args)
{
  self->callback(self->context, args);
}