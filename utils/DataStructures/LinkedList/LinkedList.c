#include "LinkedList.h"

void LinkedList_Init(LinkedList_t *instance)
{
  instance->head.next = &instance->head;
}

void LinkedList_Push(LinkedList_t *instance, LinkedListNode_t *node)
{
  LinkedListNode_t *current = instance->head.next;

  while (current->next != &instance->head)
  {
    current = current->next;
  }

  current->next = node;
  node->next = &instance->head;
}

LinkedListNode_t *LinkedList_Pop(LinkedList_t *instance)
{
  LinkedListNode_t *previous = instance->head.next;
  LinkedListNode_t *current = instance->head.next;

  while (current->next != &instance->head)
  {
    previous = current;
    current = current->next;
  }

  previous->next = &instance->head;
  return current;
}

void LinkedList_Remove(LinkedList_t *instance, LinkedListNode_t *node)
{
  LinkedListNode_t *previous = instance->head.next;
  LinkedListNode_t *current = instance->head.next;

  while (current->next != &instance->head)
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

uint16_t LinkedList_Count(LinkedList_t *instance)
{
  uint16_t count = 0;
  LinkedListNode_t *current = instance->head.next;

  while (current != &instance->head)
  {
    count++;
    current = current->next;
  }
  return count;
}

bool LinkedList_Contains(LinkedList_t *instance, LinkedListNode_t *node)
{
  LinkedListNode_t *current = instance->head.next;

  while (current != &instance->head)
  {
    if (current == node)
    {
      return true;
    }
  }
  return false;
}

uint16_t LinkedList_IndexOf(LinkedList_t *instance, LinkedListNode_t *node)
{
  uint16_t index = 0;
  LinkedListNode_t *current = instance->head.next;

  while (current != &instance->head)
  {
    index++;
    if (current == node)
    {
      return index;
    }
    current = current->next;
  }
  return 0;
}
