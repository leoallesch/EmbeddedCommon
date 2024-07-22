#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>
#include <stdint.h>

typedef struct LinkedListNode_t
{
  struct LinkedListNode_t *next;
} LinkedListNode_t;

typedef struct
{
  LinkedListNode_t head;
} LinkedList_t;

typedef struct
{
  LinkedListNode_t *current;
} LinkedListIter_t;

void LinkedList_Init(LinkedList_t *self);

void LinkedList_PushFront(LinkedList_t *self, LinkedListNode_t *node);

void LinkedList_PushBack(LinkedList_t *self, LinkedListNode_t *node);

void LinkedList_InsertAfter(LinkedList_t *self, LinkedListNode_t *after, LinkedListNode_t *node);

LinkedListNode_t *LinkedList_PopFront(LinkedList_t *self);

LinkedListNode_t *LinkedList_PopBack(LinkedList_t *self);

void LinkedList_Remove(LinkedList_t *self, LinkedListNode_t *node);

bool LinkedList_Contains(LinkedList_t *self, LinkedListNode_t *node);

uint16_t LinkedList_IndexOf(LinkedList_t *self, LinkedListNode_t *node);

uint16_t LinkedList_Count(LinkedList_t *self);

void LinkedListIter_Init(LinkedListIter_t *self, LinkedList_t *list);

LinkedListNode_t *LinkedListIter_Next(LinkedListIter_t *self, LinkedList_t *list);

#define LinkedList_ForEach(_list, _type, _item, ...)             \
  do                                                             \
  {                                                              \
    LinkedListIter_t iter;                                       \
    LinkedListIter_Init(&iter, _list);                           \
    _type *_item;                                                \
    while ((_item = (_type *)LinkedListIter_Next(&iter, _list))) \
    {                                                            \
      __VA_ARGS__                                                \
    }                                                            \
  } while (0)

#endif