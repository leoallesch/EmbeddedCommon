#ifndef I_UART_H
#define I_UART_H

#include <stdint.h>
#include "I_Event.h"

typedef struct
{
  uint8_t byte;
} UART_OnReceiveArgs_t;

struct I_UART_Api_t;

typedef struct
{
  const struct I_UART_Api_t *api;
} I_UART_t;

typedef struct I_UART_Api_t
{
  void (*Send)(I_UART_t *self, uint8_t byte);
  I_Event_t *(*OnSendComplete)(I_UART_t *self);
  I_Event_t *(*OnReceive)(I_UART_t *self);
} I_UART_Api_t;

#define UART_Send(uart, byte) \
  (uart)->api->Send((uart), (byte))

#define UART_OnSendComplete(uart) \
  (uart)->api->OnSendComplete((uart))

#define UART_OnReceive(uart) \
  (uart)->api->OnReceive((uart))

#endif