#include "SmartCalc_v1_0.h"

stack* init_stack() {
    stack* stack = malloc(sizeof(stack));
    stack->top = init_list(NULL);
    return stack;
}

void push(stack* stack, lexeme* lex) {
    add(stack->top, lex);
}

lexeme* pop(stack* stack) {
    node* elem_node = stack->top->next;
    if (elem_node == NULL) {
        return NULL;
    } else {
        lexeme* lex = elem_node->lex;
        stack->top = del_elem(elem_node, stack->top);
        return lex;
    }
}

lexeme* peek(stack* stack) {
    node* elem_node = stack->top->next;
    if (elem_node == NULL) {
        return NULL;
    } else {
        return elem_node->lex;
    }
}

int is_empty(stack* stack) {
    if (stack->top == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void del_stack(stack* stack, int flag) {
    if (flag == 0) {
        if (stack != NULL) {
            del_list(stack->top, 0);
            free(stack);
            stack = NULL;
        }
    } else {
        if (stack->top != NULL) {
            del_list(stack->top, 1);
        }
        free(stack);
        stack = NULL;
    }
}

node* init_list(lexeme* lex) {
    node* list = (node*)malloc(sizeof(node));
    if (list != NULL) {
        list->lex = lex;
        list->next = NULL;
    }
    return list;
}

node* add(node* elem, lexeme* lex) {
    if (elem != NULL) {
        node* afterNext = elem->next;
        node* newNode = init_list(lex);
        elem->next = newNode;
        newNode->next = afterNext;
        return newNode;
    } else {
        return NULL;
    }
}

node* del_elem(node* elem, node* root) {
    if (elem == NULL || root == NULL) {
        return root;
    } else {
        node* prev = NULL;
        node* p = root;
        while (p != NULL && prev == NULL) {
            if (p->next == elem) {
                prev = p;
            } else {
                p = p->next;
            }
        }
        if (prev == NULL) {
            if (root == elem) {
                node* newRoot = root->next;
                free(elem);
                return newRoot;
            } else {
                return root;
            }
        } else {
            prev->next = elem->next;
            free(elem);
            return root;
        }
    }
}

node* add_to_end(node* root, lexeme* lex) {
    if (root == NULL) {
        root = init_list(lex);
    } else {
        node* p = root;
        while (p->next != NULL) {
            p = p->next;
        }
        add(p, lex);
    }
    return root;
}

void del_list(node* root, int flag_free_elements) {
    node* p = root;
    while (p != NULL) {
        node* currentNode = p;
        p = p->next;
        if (flag_free_elements == 1) {
            if (currentNode->lex != NULL) {
                del_lexeme(currentNode->lex);
            }
        }
        free(currentNode);
        currentNode = NULL;
    }
}

void del_lexeme(lexeme* lex) {
    if (lex != NULL) {
        if (lex->s != NULL) {
            free(lex->s);
            lex->s = NULL;
        }
        free(lex);
        lex = NULL;
    }
}

void print_lexeme(lexeme* lex) {
    if (lex->type == 'f') {
        printf("%s ", lex->s);
    } else if (lex->type == 'u') {
        if (lex->c == '-') {
            printf("M ");
        } else {
            printf("P ");
        }
    } else if (lex->type == 'o') {
        printf("%c ", lex->c);
    } else if (lex->type == '(') {
        printf("( ");
    } else if (lex->type == ')') {
        printf(") ");
    } else if (lex->type == 'v') {
        printf("%g ", lex->v);
    } else if (lex->type == 'x') {
        printf("x ");
    }
}

/**
 * @brief преобразует унарные + и - в специальные лексемы
 **/
void unary_process(node* lexemes) {
    lexeme* prev_lexeme = NULL;
    node* p = lexemes;
    while (p != NULL) {
        // Если предыдущая лексема оператор или откр.скобка либо предыдущей лексемы
        // нет, а текущая лексема - или +, то текущая лексема унарная
        if (prev_lexeme == NULL || prev_lexeme->type == 'o' ||
            prev_lexeme->type == 'u' || prev_lexeme->type == '(') {
            if (p->lex->c == '-' || p->lex->c == '+') {
                p->lex->type = 'u';
            }
        }

        prev_lexeme = p->lex;
        p = p->next;
    }
}

/**
 * @brief функция "парсинга" лексем;
 * @param state 4 состояния:
 * 1: 0 - 9;
 * 2: a - z;
 * 3: +, -, /, *;
 * 4: (, );
 * @return lexeme
 **/
lexeme* create_lexeme(char* buf, int state) {
    lexeme* lex = NULL;
    if (buf == NULL) {
        // lex NULL;
    } else if (state == 1) {
        lex = (lexeme*)malloc(sizeof(lexeme));
        if (lex != NULL) {
            lex->type = 'v';
            lex->s = NULL;
            lex->c = '0';
            int n = 0;
            if (sscanf(buf, "%lf%n", &lex->v, &n) == 0) {
                free(lex);
                lex = NULL;
            } else {
                if (buf[n] != '\0') {
                    free(lex);
                    lex = NULL;
                }
            }
        }
    } else if (state == 2) {
        if (strcmp(buf, "cos") == 0 || strcmp(buf, "sin") == 0 ||
            strcmp(buf, "tan") == 0 || strcmp(buf, "acos") == 0 ||
            strcmp(buf, "asin") == 0 || strcmp(buf, "atan") == 0 ||
            strcmp(buf, "sqrt") == 0 || strcmp(buf, "ln") == 0 ||
            strcmp(buf, "log") == 0 || strcmp(buf, "mod") == 0 ||
            strcmp(buf, "x") == 0) {
            lex = (lexeme*)malloc(sizeof(lexeme));
            if (lex != NULL) {
                if (strcmp(buf, "mod") == 0) {
                    lex->type = 'o';
                    lex->c = 'm';
                    lex->v = 0.0;
                    lex->s = NULL;
                } else if (strcmp(buf, "x") == 0) {
                    lex->type = 'x';
                    lex->s = NULL;
                    lex->c = '0';
                    lex->v = 0.0;
                } else {
                    lex->type = 'f';
                    lex->s = (char*)malloc((strlen(buf) + 1) * sizeof(char));
                    strcpy(lex->s, buf);
                    lex->c = '0';
                    lex->v = 0.0;
                }
            }
        }
    } else if (state == 3) {
        lex = (lexeme*)malloc(sizeof(lexeme));
        if (lex != NULL) {
            lex->type = 'o';
            lex->s = NULL;
            lex->c = *buf;
            lex->v = 0.0;
        }
    } else if (state == 4) {
        lex = (lexeme*)malloc(sizeof(lexeme));
        if (lex != NULL) {
            lex->type = *buf;
            lex->s = NULL;
            lex->v = 0.0;
            lex->c = '0';
        }
    }
    return lex;
}

/**
 * @brief функция разбриает строку на лексемы;
 * @param parse_exception_index если 0 функция отработала хорошо, иначе ошибка;
 * @return возвращает список лексем;
 **/
node* parse_lexemes(char* in, int* parse_exception_index) {
    node* lexemes = NULL;
    *parse_exception_index = 2;
    if (in != NULL && strlen(in) != 0) {
        *parse_exception_index = 0;
        char* cin = in;
        char* buf = NULL;
        int sizeMalloc = 0;
        int n = 0;

        /*
        state = 1: 0 - 9;
        state = 2: a - z;
        state = 3: + - / * ^;
        state = 4: ();
        */
        int state = 0;
        if (cin != NULL) {
            while (*parse_exception_index == 0) {
                if ((*cin >= '0' && *cin <= '9') || *cin == '.') {
                    if (state != 1 && state != 0) {
                        buf[n] = '\0';
                        lexeme* lex = create_lexeme(buf, state);
                        if (lex == NULL) {
                            *parse_exception_index = 1;
                            break;
                        }
                        lexemes = add_to_end(lexemes, lex);
                        n = 0;
                    }
                    state = 1;
                } else if (*cin >= 'a' && *cin <= 'z') {
                    if (state != 2 && state != 0) {
                        buf[n] = '\0';
                        lexeme* lex = create_lexeme(buf, state);
                        if (lex == NULL) {
                            *parse_exception_index = 1;
                            break;
                        }
                        lexemes = add_to_end(lexemes, lex);
                        n = 0;
                    }
                    state = 2;
                } else if (*cin == '+' || *cin == '-' || *cin == '*' || *cin == '/' ||
                           *cin == '^') {
                    if (state != 0) {
                        buf[n] = '\0';
                        lexeme* lex = create_lexeme(buf, state);
                        if (lex == NULL) {
                            *parse_exception_index = 1;
                            break;
                        }
                        lexemes = add_to_end(lexemes, lex);
                        n = 0;
                    }
                    state = 3;
                } else if (*cin == '(' || *cin == ')') {
                    if (state != 0) {
                        buf[n] = '\0';
                        lexeme* lex = create_lexeme(buf, state);
                        if (lex == NULL) {
                            *parse_exception_index = 1;
                            break;
                        }
                        lexemes = add_to_end(lexemes, lex);
                        n = 0;
                    }
                    state = 4;
                } else if (*cin == '\0' || *cin == '=') {
                    if (state != 0) {
                        buf[n] = '\0';
                        lexeme* lex = create_lexeme(buf, state);
                        if (lex == NULL) {
                            *parse_exception_index = 1;
                            break;
                        }
                        lexemes = add_to_end(lexemes, lex);
                        n = 0;
                    }
                    break;
                } else if (*cin == ' ' && state != 0) {
                    buf[n] = '\0';
                    if (strcmp(buf, "x") == 0) {
                        lexeme* lex = create_lexeme(buf, state);
                        if (lex == NULL) {
                            *parse_exception_index = 1;
                            break;
                        }
                        lexemes = add_to_end(lexemes, lex);
                        n = 0;
                        state = 0;
                    } else if (strcmp(buf, "mod") == 0) {
                        lexeme* lex = create_lexeme(buf, state);
                        if (lex == NULL) {
                            *parse_exception_index = 1;
                            break;
                        }
                        lexemes = add_to_end(lexemes, lex);
                        n = 0;
                        state = 0;
                    }
                }
                if (*cin != ' ' && *parse_exception_index == 0) {
                    if (sizeMalloc <= n) {
                        sizeMalloc += 10;
                        char* tmp = (char*)realloc(buf, (sizeMalloc + 1) * sizeof(char));
                        if (tmp == NULL) {
                            *parse_exception_index = 1;
                            break;
                        } else {
                            buf = tmp;
                        }
                    }
                    buf[n] = *cin;
                    n++;
                }
                cin++;
            }
        }
        if (lexemes != NULL && *parse_exception_index == 0) {
            unary_process(lexemes);
        }
        if (*parse_exception_index > 0) {
            del_list(lexemes, 1);
        }
        if (buf != NULL) {
            free(buf);
        }
    }
    return lexemes;
}

/**
 * @brief Преобразует в польскую нотацию
 * @param syntax_exception_type ссылка на ошибки:
 *          0: OK;
 *          1: несовместимые скобки;
 **/
node* reverse_polish_notation(node* ipn, int* syntax_exception_type) {
    *syntax_exception_type = 0;
    node* clear = NULL;
    node* result = NULL;

    if (ipn != NULL) {
        stack* Stack = init_stack();
        node* cipn = ipn;
        while (cipn != NULL && *syntax_exception_type == 0) {
            if (cipn->lex->type == 'f' || cipn->lex->type == 'u') {
                if (cipn->lex->type == 'u') {
                    push(Stack, cipn->lex);
                } else {
                    if (cipn->next != NULL) {
                        if (cipn->next->lex->type == '(') {
                            push(Stack, cipn->lex);
                        } else {
                            *syntax_exception_type = 6;
                            break;
                        }
                    } else {
                        *syntax_exception_type = 6;
                        break;
                    }
                }
            } else if (cipn->lex->type == 'o') {
                lexeme* op1 = cipn->lex;

                /*
                Пока присутствует на вершине стека лексема-оператор (op2) чей приоритет
                выше приоритета O1, либо при равенстве приоритетов op1 является
                левоассоциативным: Перекладываем op2 из стека в выходную очередь.
                */
                // Переложить op2 из стека в выходную очередь:
                while (is_empty(Stack) == 0) {
                    lexeme* op2 = peek(Stack);
                    if ((op2->type != 'o' && op2->type != 'u') ||
                        (op1->c == '^' && op2->c != '^') ||
                        ((op1->c == '*' || op1->c == '/' || op1->c == 'm') &&
                         (op2->c == '+' || op2->c == '-'))) {
                        break;
                    } else {
                        pop(Stack);
                        result = add_to_end(result, op2);
                    }
                }
                // Положить op1 в стек
                push(Stack, op1);
            } else if (cipn->lex->type == '(') {
                // если токен открыающая скобка положим его в стек;
                push(Stack, cipn->lex);
            } else if (cipn->lex->type == ')') {
                /*
                если токен закрывающая скобка, пока токен на вершине стека не
                открывающая скобка переложить оператор из стека в выходную очередь;
                */
                int open_bracket_found = 0;
                while (is_empty(Stack) == 0) {
                    lexeme* op2 = peek(Stack);
                    if (op2->type != '(') {
                        pop(Stack);
                        result = add_to_end(result, op2);
                    } else {
                        open_bracket_found = 1;
                        // Выкинуть открывающую скобку из стека, но не добавлять в очередь
                        // вывода.
                        clear = add_to_end(clear, pop(Stack));
                        break;
                    }
                }
                if (open_bracket_found == 0) {
                    // если не нашли открывающую скобку, вывод ошибки:
                    *syntax_exception_type = 5;
                    clear = add_to_end(clear, cipn->lex);
                } else {
                    clear = add_to_end(clear, cipn->lex);
                }

                // Если токен на вершине стека — функция, переложить её в выходную
                // очередь.
                lexeme* op2 = peek(Stack);
                if (op2 != NULL && op2->type == 'f') {
                    pop(Stack);
                    result = add_to_end(result, op2);
                }
            } else {
                // Если токен — число, то добавить его в очередь вывода.
                result = add_to_end(result, cipn->lex);
            }
            cipn = cipn->next;
        }

        if (*syntax_exception_type == 0) {
            /*
            Если больше не осталось токенов на входе:
            пока есть токены операторы в стеке:
            переложить оператор из стека в выходную очередь.
            */
            while (is_empty(Stack) == 0) {
                lexeme* op2 = peek(Stack);

                if (op2->type == 'o' || op2->type == 'u' || op2->type == 'f') {
                    pop(Stack);
                    result = add_to_end(result, op2);
                } else {
                    // только операторы (и возможно функции) должны оставаться в стеке
                    *syntax_exception_type = 1;
                    break;
                }
            }
        }
        if (*syntax_exception_type != 0) {
            if (*syntax_exception_type == 1) {
                if (result != NULL) {
                    del_list(result, 1);
                }
                del_list(ipn, 0);
                del_stack(Stack, 1);
                del_list(clear, 1);
            } else if (*syntax_exception_type == 5) {
                if (result != NULL) {
                    del_list(result, 1);
                }
                del_stack(Stack, 0);
                while (cipn != NULL) {
                    node* p = cipn;
                    del_lexeme(p->lex);
                    cipn = cipn->next;
                }
                del_list(ipn, 0);
                del_list(clear, 1);
            } else {
                if (result != NULL) {
                    del_list(result, 0);
                }
                del_stack(Stack, 0);
                del_list(ipn, 1);
            }
        } else {
            del_list(ipn, 0);
            del_stack(Stack, 1);
            del_list(clear, 1);
        }
    }
    return result;
}

double result_polish_notation(double x, char* in, int* error) {
    *error = 0;
    double res = 0;
    node* ipn = parse_lexemes(in, error);
    if (*error == 0) {
        node* rpn = reverse_polish_notation(ipn, error);
        if (rpn != NULL) {
            if (*error == 0) {
                res = evaluate(x, rpn, error);
                if (*error != 0) {
                    res = 0;
                }
            }
        } else {
            *error = 1;
        }
    }
    return res;
}

/**
 * @brief
 * @param exec_exception_type записывается ошибка вывода:
 * 0: все хорошо;
 * 1: неправильное выражение;
 * 2: деление на 0;
 * 3: число равно бесконечности;
 * 4: ошибка функции, ln, log, sqrt не могут быть отрицательными;
 * @return double
 **/
double evaluate(double x, node* lexemes_rpn, int* exec_exception_type) {
    *exec_exception_type = 0;

    stack* Stack = init_stack();
    node* garbage = NULL;

    node* p = lexemes_rpn;
    while (p != NULL && *exec_exception_type == 0) {
        if (p->lex->type == 'v' || p->lex->type == 'x') {
            push(Stack, p->lex);
        } else if (p->lex->type == 'o') {
            lexeme* op2 = pop(Stack);
            if (op2 == NULL) {
                *exec_exception_type = 1;
                break;
            }
            double v2 = op2->type == 'x' ? x : op2->v;
            lexeme* op1 = pop(Stack);
            if (op1 == NULL) {
                *exec_exception_type = 1;
                break;
            }
            double v1 = op1->type == 'x' ? x : op1->v;

            double res = 0;
            if (p->lex->c == '+') {
                res = v1 + v2;
            } else if (p->lex->c == '-') {
                res = v1 - v2;
            } else if (p->lex->c == '*') {
                res = v1 * v2;
            } else if (p->lex->c == '/') {
                if (v2 != 0.0) {
                    res = v1 / v2;
                    if (isinf(res)) {
                        *exec_exception_type = 3;
                    }
                } else {
                    *exec_exception_type = 2;
                }
            } else if (p->lex->c == '^') {
                res = pow(v1, v2);
            } else if (p->lex->c == 'm') {
                if (v2 != 0.0) {
                    if ((int)v1 == v1 && (int)v2 == v2) {
                        res = (int)v1 % (int)v2;
                    } else {
                        res = fmod(v1, v2);
                    }
                } else {
                    *exec_exception_type = 2;
                }
            }

            if (*exec_exception_type == 0) {
                lexeme* resLex = malloc(sizeof(lexeme));
                resLex->type = 'v';
                resLex->v = res;
                resLex->c = '0';
                resLex->s = NULL;
                garbage = add_to_end(garbage, resLex);
                push(Stack, resLex);
            }
        } else if (p->lex->type == 'u') {
            lexeme* op1 = pop(Stack);
            if (op1 == NULL) {
                *exec_exception_type = 1;
                break;
            }
            double v1 = op1->type == 'x' ? x : op1->v;

            double res = 0;
            if (p->lex->c == '-') {
                res = -v1;
            } else {
                res = v1;
            }

            lexeme* resLex = malloc(sizeof(lexeme));
            resLex->type = 'v';
            resLex->v = res;
            resLex->c = '0';
            resLex->s = NULL;
            garbage = add_to_end(garbage, resLex);
            push(Stack, resLex);
        } else if (p->lex->type == 'f') {
            lexeme* op1 = pop(Stack);
            if (op1 == NULL) {
                *exec_exception_type = 1;
                break;
            }
            double v1 = op1->type == 'x' ? x : op1->v;

            double res = 0;

            if (strcmp(p->lex->s, "cos") == 0) {
                res = cos(v1);
            } else if (strcmp(p->lex->s, "sin") == 0) {
                res = sin(v1);
            } else if (strcmp(p->lex->s, "tan") == 0) {
                res = tan(v1);
            } else if (strcmp(p->lex->s, "acos") == 0) {
                res = acos(v1);
            } else if (strcmp(p->lex->s, "asin") == 0) {
                res = asin(v1);
            } else if (strcmp(p->lex->s, "atan") == 0) {
                res = atan(v1);
            } else if (strcmp(p->lex->s, "sqrt") == 0) {
                if (v1 >= 0) {
                    res = sqrt(v1);
                } else {
                    *exec_exception_type = 4;
                    break;
                }
            } else if (strcmp(p->lex->s, "ln") == 0) {
                if (v1 >= 0) {
                    res = log(v1);
                } else {
                    *exec_exception_type = 4;
                    break;
                }
            } else if (strcmp(p->lex->s, "log") == 0) {
                if (v1 >= 0) {
                    res = log10(v1);
                } else {
                    *exec_exception_type = 4;
                    break;
                }
            }
            lexeme* resLex = malloc(sizeof(lexeme));
            resLex->type = 'v';
            resLex->v = res;
            resLex->c = '0';
            resLex->s = NULL;
            garbage = add_to_end(garbage, resLex);
            push(Stack, resLex);
        }
        p = p->next;
    }
    double v = 0;

    if (*exec_exception_type == 0) {
        lexeme* lex = pop(Stack);
        v = lex->type == 'x' ? x : lex->v;

        // убеждаемся что стек пуст;
        if (is_empty(Stack) != 1) {
            *exec_exception_type = 1;
        }
    }

    // очищаем все;
    del_list(garbage, 1);
    del_list(lexemes_rpn, 1);
    del_stack(Stack, 0);
    return v;
}