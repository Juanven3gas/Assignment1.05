#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

int queue_init(queue_t *q)
{
  q->size = 0;
  //q->head = q->tail = NULL;
  q->head = (queue_node_t *)malloc(sizeof(queue_node_t));
  q->tail = (queue_node_t *)malloc(sizeof(queue_node_t));
  q->head->next = NULL;
  q->tail->next = NULL;
  return 0;
}

int queue_delete(queue_t *q)
{
  monster_t m;

  while (!queue_remove(q, &m))
    ;

  free(q->head);
  free(q->tail);
  return 0;
}

int queue_add(queue_t *q, monster_t m, int priority)
{
  //If the queue is not empty
  if (q->head->next != NULL) 
  {

    queue_node_t *toAdd = (queue_node_t *)malloc(sizeof(queue_node_t));
    
    if(toAdd == NULL)
    {
      fprintf(stderr, "Out of memory.\n");
      return 1;
    }
    /*if (!(q->tail->next = malloc(sizeof (*q->tail->next)))) {
      fprintf(stderr, "Out of memory.\n");

      return 1;
    }*/

    toAdd->monster = m;
    toAdd->priority = priority;

    queue_node_t *cursor = q->head->next;
    queue_node_t *previous = q->head;
    int addedFlag = 0;

    while(cursor->next != NULL)
    {
      if(cursor->priority > toAdd->priority)
      {
        toAdd->next = cursor;
        previous->next = toAdd;
        addedFlag = 1;
        break;
      }
      previous = cursor;
      cursor = cursor->next;
    }

    if(!addedFlag)
    {
      toAdd->next = cursor;
      previous->next = toAdd;

      /*q->tail->next = toAdd;
      toAdd->next = NULL;
      q->tail = q->tail->next;*/
    }

    /*q->tail = q->tail->next;
    q->tail->value = v;
    q->tail->next = NULL;*/
    q->size++;

    return 0;
  } 
  else 
  {
    queue_node_t *toAdd = (queue_node_t *)malloc(sizeof(queue_node_t));
    if(toAdd == NULL)
    {
      fprintf(stderr, "Out of memory.\n");
      
      return 1;
    }

    toAdd->monster = m;
    toAdd->priority = priority;
    /*if (!(q->tail = q->head = malloc(sizeof (*q->tail)))) {
      fprintf(stderr, "Out of memory.\n");

      return 1;
    }*/

    q->head->next = toAdd;
    toAdd->next= q->tail;
    /*q->tail->value = v;
    q->tail->priority = priority;
    q->tail->next = NULL;*/
    q->size++;

    return 0;
  }

  return 0; /* Won't be reached */
}

int queue_remove(queue_t *q, monster_t *m)
{
  queue_node_t *n;

  //if the queue is empty
  if (!q->size) {
    return 1;
  }

  n = q->head->next;

  q->head->next = n->next;
  q->size--;
  *m = n->monster;
  free(n);

  /*if (!q->size) {
    q->tail = NULL;
  }*/

  return 0;
}

int queue_peek(queue_t *q, monster_t *m)
{
  if (q->size) {
    *m = q->head->next->monster;

    return 0;
  }

  return 1;
}

int queue_size(queue_t *q)
{
  return q->size;
}