#ifndef I_EVENT_H
#define I_EVENT_H

#include "EventSubscription.h"

struct I_Event_Api_t;

typedef struct
{
  const struct I_Event_Api_t *api;
} I_Event_t;

typedef struct I_Event_Api_t
{
  void (*Subscribe)(I_Event_t *self, EventSubscription_t *subscription);
  void (*Unsubscribe)(I_Event_t *self, EventSubscription_t *subscription);
} I_Event_Api_t;

#define Event_Subscribe(_event, _sub) \
  (_event)->api->Subscribe((_event), (_sub))

#define Event_Unsubscribe(_event, _sub) \
  (_event)->api->Unsubscribe((_event), (_sub))

#endif