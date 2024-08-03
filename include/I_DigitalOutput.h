#ifndef I_DIGITALOUTPUT_H
#define I_DIGITALOUTPUT_H

#include <stdbool.h>

struct I_DigitalOutput_Api_t;

typedef struct
{
  const struct I_DigitalOutput_Api_t *api;
} I_DigitalOutput_t;

typedef struct I_DigitalOutput_Api_t
{
  void (*Write)(I_DigitalOutput_t *self, bool val);
} I_DigitalOutput_Api_t;

#define DigitalOutput_Write(_self, _val) \
  (_self)->api->Write((_self), (_val))

#endif