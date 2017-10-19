#ifndef PRIORITY_QUEUE_H
# define PRIORITY_QUEUE_H
#include "gen_dun.h"

/*typedef struct monster 
{
    int x_pos;
    int y_pos;
    int room;
    int characteristics;
    int speed;
    int move;
    int alive;
} monster_t;*/

typedef struct queue_node {
  //int value;
  int priority;
  monster_t monster;
  struct queue_node *next;
} queue_node_t;

typedef struct queue {
  int size;
  queue_node_t *head, *tail;
} queue_t;

int queue_init(queue_t *q);
int queue_delete(queue_t *q);
int queue_empty(queue_t *q);
//int queue_add(queue_t *q, int v, int priority);
//int queue_remove(queue_t *q, int *v);
//int queue_peek(queue_t *q, int *v);
int queue_add(queue_t *q, monster_t m, int priority);
int queue_remove(queue_t *q, monster_t *m);
int queue_peek(queue_t *q, monster_t *m);

int queue_size(queue_t *q);

#endif