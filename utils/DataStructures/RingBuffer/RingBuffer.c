#include "RingBuffer.h"

#include <stdint.h>
#include <string.h>

void RingBuffer_Init(
    RingBuffer_t *instance,
    void *buffer,
    unsigned elementSize,
    unsigned elementCount)
{
    instance->buffer = buffer;
    instance->elementSize = elementSize;
    instance->capacity = elementCount;

    RingBuffer_Clear(instance);
}

extern inline unsigned RingBuffer_Capacity(RingBuffer_t *instance);

unsigned RingBuffer_Count(RingBuffer_t *instance)
{
    if (instance->full)
    {
        return instance->capacity;
    }

    unsigned count = instance->head - instance->tail;

    return count;
}

void RingBuffer_At(RingBuffer_t *instance, unsigned index, void *element);

void RingBuffer_Push(RingBuffer_t *instance, const void *data)
{
    unsigned next = instance->head + 1;
    if (next >= instance->capacity)
    {
        next = 0;
    }

    if (next == instance->tail)
    {
        instance->full = true;
        return;
    }

    uint8_t *d = (uint8_t *)instance->buffer + next * instance->elementSize;
    memcpy(d, data, instance->elementSize);
    instance->head = next;
}

void RingBuffer_Pop(RingBuffer_t *instance, void *element);

void RingBuffer_Clear(RingBuffer_t *instance)
{
    instance->head = 0;
    instance->tail = 0;
    instance->full = false;
}
