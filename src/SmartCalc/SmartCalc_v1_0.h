#ifndef SRC_SMARTCALC_V1_0_H_
#define SRC_SMARTCALC_V1_0_H_
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lexeme {
  char c;
  char* s;
  double v;
  char type;
  /**
   * f: function
   * u: unary - or +
   * o: operation + - * /
   * (: literal (
   * ): literal )
   * v: value
   * x: literal x
   **/
} lexeme;

typedef struct Node {
  lexeme* lex;
  struct Node* next;
} node;

typedef struct Stack {
  node* top;
} stack;

typedef struct Cordinate {
  double x;
  double y;
} cordinate;

typedef struct deposit_calculation_result0 {
  double interest_charges;
  double tax_amount;
  double amount_end_term;
} deposit_calculation_result;

typedef struct daynum_sum0 {
  int daynum;
  double sum;
} daynum_sum;

// STACK
stack* init_stack();
void push(stack* stack, lexeme* lex);
lexeme* pop(stack* stack);
lexeme* peek(stack* stack);
int is_empty(stack* stack);
void del_stack(stack* stack, int flag);

// LIST
node* init_list(lexeme* lex);
node* add(node* elem, lexeme* lex);
node* add_to_end(node* root, lexeme* lex);
node* del_elem(node* elem, node* root);
void del_list(node* root, int flag_free_elements);
void del_lexeme(lexeme* lex);

// MAIN_FUNCS
lexeme* create_lexeme(char* buf, int state);
void unary_process(node* lexemes);
node* parse_lexemes(char* in, int* parse_exception_index);
node* reverse_polish_notation(node* inp, int* syntax_exception_type);
double result_polish_notation(double x, char* in, int* error);
double evaluate(double x, node* lexemes_rpn, int* exec_exception_type);

// ADDITINAL_TASKS_FUNCS
cordinate* graph_output_points(double xBegin, double xEnd, int points,
                               char* expression, int* error);
daynum_sum* pars_replen_and_withdrawal(char* str, int* n_pars, int* error);
deposit_calculation_result* calculate_deposit(
    double deposit_amount, int period_days, double rate_per_day,
    int payment_periodicity_days, int capitalization, double tax_rate_per_year,
    daynum_sum* replenishment, daynum_sum* withdrawals, int n_replen,
    int n_withd);

#endif  // SRC_SMARTCALC_V1_0_H_
