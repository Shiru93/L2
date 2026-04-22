#ifndef STACK_LINK_H
#define STACK_LINK_H

#include "binary_tree.h"

struct stack {
  int top; /* height of the stack */
  link *content;
};

struct stack * init_stack(int);
void delete_stack(struct stack **);
int is_empty_stack(const struct stack *);
void push_stack(struct stack *, link);
link pop_stack(struct stack *);

#endif
