#ifndef I_DIGITALINPUT_H
#define I_DIGITALINPUT_H

#include <stdbool.h>

struct I_DigitalInput_Api_t;

typedef struct
{
  const struct I_DigitalInput_Api_t *api;
} I_DigitalInput_t;

typedef struct I_DigitalInput_Api_t
{
  bool (*Read)(I_DigitalInput_t *self);
} I_DigitalInput_Api_t;

#define DigitalInput_Read(_self) \
  (_self)->api->Read((_self))

#endif