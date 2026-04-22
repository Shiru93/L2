#ifndef QUEUE_LINK_H
#define QUEUE_LINK_H

#include "binary_tree.h"

struct node_Q {
  link value; /* value of node */
  struct node_Q *next; /* pointer to next node */
};
struct queue {
  struct node_Q *first; /* pointer to first node of queue */
  struct node_Q *last; /* pointer to last node of queue */
};

struct node_Q * new_node_Q(link);
void delete_node_Q(struct node_Q **);
struct queue * init_queue();
void delete_queue(struct queue **);
int is_empty_queue(const struct queue *);
link dequeue(struct queue *);
void enqueue(struct queue *, link);

#endif
