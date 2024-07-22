#include "Event.h"

static void Subscribe(I_Event_t *self, EventSubscription_t *subscription)
{
  Event_t *event = (Event_t *)self;
  LinkedList_Remove(&event->subscribers, &subscription->node);
  LinkedList_Push(&event->subscribers, &subscription->node);
}

static void Unsubscribe(I_Event_t *self, EventSubscription_t *subscription)
{
  Event_t *event = (Event_t *)self;
  LinkedList_Remove(&event->subscribers, &subscription->node);
}

static const I_Event_Api_t api = {Subscribe, Unsubscribe};

void Event_Init(Event_t *self)
{
  self->interface.api = &api;
  LinkedList_Init(&self->subscribers);
}

void Event_Publish(Event_t *self, const void *args)
{
  LinkedList_ForEach(&self->subscribers, EventSubscription_t, subscription, {
    EventSubscription_Publish(subscription, args);
  });
}
