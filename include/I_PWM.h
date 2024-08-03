#ifndef I_PWM_H
#define I_PWM_H

#include <stdint.h>

typedef uint8_t PWM_DutyCycle_t;
typedef uint8_t PWM_Freq_t;

struct I_PWM_Api_t;

typedef struct
{
  const struct I_PWM_Api_t *api;
} I_PWM_t;

typedef struct I_PWM_Api_t
{
  void (*SetDutyCycle)(I_PWM_t *self, PWM_DutyCycle_t dutyCycle);
  void (*SetFrequency)(I_PWM_t *self, PWM_Freq_t freq);
} I_PWM_Api_t;

#define PWM_SetDutyCycle(_self, _duty) \
  (_self)->api->SetDutyCycle((_self), (_duty))

#define PWM_SetFrequency(_self, _freq) \
  (_self)->api->SetFrequency((_self), (_freq))

#endif