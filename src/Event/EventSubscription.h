#ifndef EVENTSUBSCRIPTION_H
#define EVENTSUBSCRIPTION_H

#include "LinkedList.h"

typedef void (*EventCallback_t)(void *context, const void *args);

typedef struct
{
  LinkedListNode_t node;
  void *context;
  EventCallback_t callback;
} EventSubscription_t;

void EventSubscription_Init(EventSubscription_t *self, void *context, EventCallback_t callback);

void EventSubscription_Publish(EventSubscription_t *self, const void *args);

#endif