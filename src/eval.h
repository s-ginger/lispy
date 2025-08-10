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

long eval_op(long x, char* op, long y);
long eval(mpc_ast_t* t); 

#endif