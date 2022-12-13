#ifndef SRC_SUBMAIN_H_
#define SRC_SUBMAIN_H_

#include <stdio.h>

#define ERROR_CODE_DEFAULT -1                               // DEFAULT

//defines for priorityOperand
#define PRIORITY3 3                                         // ()
#define PRIORITY2 2                                         // /*
#define PRIORITY1 1                                         // +-
		    
//defines for isOperationAllowed
#define YES 0
#define NO 1
#define ERROR -1

int priorityOperand (int operand);                          //PRIORITY NUMBER
int isOperationAllowed(int stackOperand, int stdinOperand); //YES, NO

#endif  // SRC_SUBMAIN_H_
