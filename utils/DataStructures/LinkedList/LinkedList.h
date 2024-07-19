#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

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
} LinkedListIterator_t;

void LinkedList_Init(LinkedList_t *instance);

inline void LinkedList_PushFront(LinkedList_t *instance, LinkedListNode_t *node)
{
  node->next = instance->head.next;
  instance->head.next = node;
}

void LinkedList_Push(LinkedList_t *instance, LinkedListNode_t *node);

LinkedListNode_t *LinkedList_Pop(LinkedList_t *instance);

void LinkedList_Remove(LinkedList_t *instance, LinkedListNode_t *node);

uint16_t LinkedList_Count(LinkedList_t *instance);

bool LinkedList_Contains(LinkedList_t *instance, LinkedListNode_t *node);

uint16_t LinkedList_IndexOf(LinkedList_t *instance, LinkedListNode_t *node);

inline void LinkedListIterator_Init(LinkedListIterator_t *iter, LinkedList_t *list)
{
  iter->current = list->head.next;
}

inline LinkedListNode_t *LinkedListIterator_Next(LinkedListIterator_t *instance, LinkedList_t *list)
{
  if (instance->current == &list->head)
  {
    return NULL;
  }
  else
  {
    LinkedListNode_t *item = instance->current;
    instance->current = instance->current->next;
    return item;
  }
}

#define LinkedList_ForEach(_list, _type, _item, ...)                \
  do                                                                \
  {                                                                 \
    LinkedListIterator_t _iter;                                     \
    LinkedListIterator_Init(&_iter, _list);                         \
    _type *_item;                                                   \
    while (_item = (_type *)LinkedListIterator_Next(&_iter, _list)) \
    {                                                               \
      __VA_ARGS__                                                   \
    }                                                               \
  } while (0)

#endif