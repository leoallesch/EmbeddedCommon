#ifndef I_TIMESOURCE_H
#define I_TIMESOURCE_H

#include <stdint.h>

typedef uint16_t TimeSourceTicks_t;

struct I_TimeSource_Api_t;

typedef struct
{
  const struct I_TimeSource_Api_t *api;
} I_TimeSource_t;

typedef struct I_TimeSource_Api_t
{
  TimeSourceTicks_t (*TimeSource_Ticks)(I_TimeSource_t *instance);
} I_TimeSource_Api_t;

#define TimeSource_Ticks(instance) \
  (instance)->api->TimeSource_Ticks((instance))

#endif