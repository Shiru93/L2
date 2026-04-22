#include "stack_link.h"
#include <stdlib.h>
#include <stdio.h>

struct stack * init_stack(int maxTop) {
  struct stack *s = malloc(sizeof(struct stack));
  s->top = 0;
  s->content = malloc(maxTop*sizeof(link));
  return s;
}

void delete_stack(struct stack **s) {
  free((*s)->content);
  free(*s);
  *s = NULL;
}

int is_empty_stack(const struct stack *s) {
  return s->top == 0;
}

void push_stack(struct stack *s, link val) {
  s->content[s->top++] = val;
}

link pop_stack(struct stack *s) {
  return s->content[--s->top];
}
