#ifndef EVAL_H
#define EVAL_H

#include "mpc.h"

enum { LVAL_NUM, LVAL_ERR };

enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

typedef struct {
  int type;
  long num;
  int err;
} lval;

lval lval_num(long x);
lval lval_err(int x);
void lval_println(lval v);
void lval_print(lval v);

lval eval_op(lval x, char* op, lval y);
lval eval(mpc_ast_t* t); 

#endif