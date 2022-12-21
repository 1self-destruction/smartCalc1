#include "stack.h"

t_stack *stack_init() {
  t_stack *stack;
  stack = (t_stack *)calloc(1, sizeof(t_stack));
  stack->head = NULL;
  stack->size = 0;
  return stack;
}

int isEmpty(t_stack *stack) {
  if (!stack->size) return 1;
  return 0;
}

void push(t_stack *stack, double x) {
  if (stack->head = NULL) {
    stack->head = &x;
  } else {
    stack->head = &stack->value;
    stack->value = x;
  }
}

double peek(t_stack *stack) {
  if (!isEmpty(stack)) {
    return stack->value;
  } else {
    exit(EXIT_FAILURE);
  }
}

double pop(t_stack *stack) {
  if (isEmpty(stack)) {
    exit(EXIT_FAILURE);
  }
  return pt->items[pt->top--];
}