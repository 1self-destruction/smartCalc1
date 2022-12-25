#include "SmartCalc_v1_0.h"

int main() {


  push(pt, 1);
  push(pt, 2);
  push(pt, 3);

  printf("The top element is %d\n", peek(pt));
  printf("The stack size is %d\n", size(pt));

  pop(pt);
  pop(pt);
  pop(pt);

  if (isEmpty(pt)) {
    printf("The stack is empty");
  } else {
    printf("The stack is not empty");
  }

  return 0;
}