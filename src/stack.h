#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "submain.h"

#define MALLOC_ERROR -2
#define DEFAULT -1
#define SUCCESS 0

typedef struct s_stack {
  int *data;
  struct s_stack *next;
} t_stack;

t_stack *create_node(int *data);
void push (t_stack **stack, int *data);
void pop (t_stack **stack);

#endif  // SRC_STACK_H_

