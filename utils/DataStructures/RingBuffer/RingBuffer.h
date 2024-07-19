#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdbool.h>

typedef struct
{
    void *buffer;
    unsigned elementSize;
    volatile unsigned head;
    volatile unsigned tail;
    unsigned capacity;
    bool full;
} RingBuffer_t;

void RingBuffer_Init(
    RingBuffer_t *instance,
    void *buffer,
    unsigned elementSize,
    unsigned elementCount);

inline unsigned RingBuffer_Capacity(RingBuffer_t *instnace)
{
    return instnace->capacity;
}

unsigned RingBuffer_Count(RingBuffer_t *instance);
void RingBuffer_At(RingBuffer_t *instance, unsigned index, void* element);
void RingBuffer_Push(RingBuffer_t *instance, const void *data);
void RingBuffer_Pop(RingBuffer_t *instance, void* element);
void RingBuffer_Clear(RingBuffer_t *instance);


#endif