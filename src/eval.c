#include "mpc.h"
#include "eval.h"



lval lval_num(long x) {
    lval v;
    v.type = LVAL_NUM;
    v.num = x;
    return v;
}

lval lval_err(int x) {
    lval v;
    v.type = LVAL_ERR;
    v.err = x;
    return v;
}

void lval_print(lval v) {
    switch (v.type)
    {
    case LVAL_NUM: printf("%li", v.num); break;

    case LVAL_ERR:
        if (v.err == LERR_DIV_ZERO) {
            printf("Error: Division By Zero!");
        }
        if (v.err == LERR_BAD_OP) {
            printf("Error: Invalid Operator!");
        }   
        if (v.err == LERR_BAD_NUM) {
            printf("Error: Invalid Number!");
        }
        break;
    }
}

void lval_println(lval v) { lval_print(v); putchar('\n'); }


long eval(mpc_ast_t* t) {
    if (strstr(t->tag, "number")) {
        return atoi(t->contents);
    }

    char* op = t->children[1]->contents;

    long x = eval(t->children[2]);

    int i = 3;
    
    while (strstr(t->children[i]->tag, "expr")) {
        x = eval_op(x, op, eval(t->children[i]));
        i++;
    }

    return x;
}


long eval_op(long x, char* op, long y) {
    if (strcmp(op, "+") == 0) { return x + y; }
    if (strcmp(op, "-") == 0) { return x - y; }
    if (strcmp(op, "*") == 0) { return x * y; }
    if (strcmp(op, "/") == 0) { return x / y; }
    return 0;
}

