#include "submain.h"

int priorityOperand (int operand) {
  int res = ERROR_CODE_DEFAULT;
    switch (operand) {
    case '*':
      res = PRIORITY2;
      break;
    case '/':
      res = PRIORITY2;
      break;
    case '-':
      res = PRIORITY1;
      break;
    case '+':
      res = PRIORITY1;
      break;
    case '(':
      res = PRIORITY3;
      break;
    case ')':
      res = PRIORITY3;
      break;
    // insert new priority here
    default:
      break;
    }
  return res;
}

int isOperationAllowed(int stackOperand, int stdinOperand) {
int res = ERROR;
  if (stackOperand >= stdinOperand) {
    res = YES;
  } else if (stackOperand < stdinOperand) {
    res = NO;
  }
return res;
}

// to add priority use:
// 
// case 'character':
//   res =  'priority_number';
//   break;
