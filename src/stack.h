#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "submain.h"

#define MALLOC_ERROR -2
#define DEFAULT -1
#define SUCCESS 0

typedef struct stack {
  double head;
  int size;
} t_stack;

int isEmpty(t_stack *pt);
void push(t_stack *pt, double x);
double peek(t_stack *pt);
double pop(t_stack *pt);

#endif  // SRC_STACK_H_
