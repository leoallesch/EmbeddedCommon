#include "LinkedList.h"

#include <stddef.h>

void LinkedList_Init(LinkedList_t *self)
{
  self->head.next = &self->head;
}

void LinkedList_PushFront(LinkedList_t *self, LinkedListNode_t *node)
{
  node->next = self->head.next;
  self->head.next = node;
}

void LinkedList_Push(LinkedList_t *self, LinkedListNode_t *node)
{
  LinkedListNode_t *current = self->head.next;

  while (current->next != &self->head)
  {
    current = current->next;
  }

  current->next = node;
  node->next = &self->head;
}

void LinkedList_Remove(LinkedList_t *self, LinkedListNode_t *node)
{
  LinkedListNode_t *previous = &self->head;
  LinkedListNode_t *current = self->head.next;

  while (current != &self->head)
  {
    if (current == node)
    {
      previous->next = current->next;
      return;
    }
    previous = current;
    current = current->next;
  }
}

bool LinkedList_Contains(LinkedList_t *self, LinkedListNode_t *node)
{
  LinkedListNode_t *current = self->head.next;

  while (current != &self->head)
  {
    if (current == node)
    {
      return true;
    }
    current = current->next;
  }
  return false;
}

uint16_t LinkedList_IndexOf(LinkedList_t *self, LinkedListNode_t *node)
{
  uint16_t index = 0;

  LinkedListNode_t *current = self->head.next;

  while (current != node && current != &self->head)
  {
    current = current->next;
    index++;
  }

  if (current == &self->head)
  {
    index++;
  }

  return index;
}

uint16_t LinkedList_Count(LinkedList_t *self)
{
  uint16_t count = 0;

  LinkedListNode_t *current = self->head.next;

  while (current != &self->head)
  {
    current = current->next;
    count++;
  }
  return count;
}

void LinkedListIter_Init(LinkedListIter_t *self, LinkedList_t *list)
{
  self->current = list->head.next;
}

LinkedListNode_t *LinkedListIter_Next(LinkedListIter_t *self, LinkedList_t *list)
{
  if (self->current == &list->head)
  {
    return NULL;
  }
  else
  {
    LinkedListNode_t *node = self->current;
    self->current = self->current->next;
    return node;
  }
}
