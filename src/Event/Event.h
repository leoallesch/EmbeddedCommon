#ifndef EVENT_H
#define EVENT_H

#include "I_Event.h"
#include "LinkedList.h"

typedef struct
{
  I_Event_t interface;
  LinkedList_t subscribers;
} Event_t;

void Event_Init(Event_t *self);

void Event_Publish(Event_t *self, const void *args);

#endif