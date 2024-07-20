#ifndef I_TIMESOURCE_H
#define I_TIMESOURCE_H

#include <stdint.h>

typedef uint32_t TimeSourceTicks_t;

struct I_TimeSource_Api_t;

typedef struct
{
  const struct I_TimeSource_Api_t *api;
} I_TimeSource_t;

typedef struct I_TimeSource_Api_t
{
  TimeSourceTicks_t (*Ticks)(I_TimeSource_t *self);
} I_TimeSource_Api_t;

#define TimeSourceTicks(_self) \
  _self->api->Ticks(_self)

#endif