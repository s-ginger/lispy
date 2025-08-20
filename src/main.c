#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"
#include "eval.h"

#ifdef _WIN32
#include <string.h>

static char buffer[2048];

/* Fake readline function */
char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

/* Fake add_history function */
void add_history(char* unused) {}

/* Otherwise include the editline headers */
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main(int argc, char const *argv[])
{

    mpc_parser_t* Number   = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Sexpr    = mpc_new("sexpr");
    mpc_parser_t* Expr     = mpc_new("expr");
    mpc_parser_t* Lispy    = mpc_new("lispy");

    /* Define them with the following Language */
    mpca_lang(MPCA_LANG_DEFAULT,
      "                                                     \
        number   : /-?[0-9]+/ ;                             \
        operator : '+' | '-' | '*' | '/' ;                  \
        sexpr  : '(' <expr>* ')' ;                          \
        expr     : <number> | '(' <operator> <expr>+ ')' ;  \
        lispy    : /^/ <operator> <expr>+ /$/ ;             \
      ",
    Number, Operator, Sexpr, Expr, Lispy);

    
    while (1) { 
        char* input = readline("lispy>");
        add_history(input);
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r)) {
            lval* x = lval_eval(lval_read(r.output));
            lval_println(x);
            lval_del(x);
            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

       
        free(input);
    }

    mpc_cleanup(4, Number, Operator, Sexpr, Expr, Lispy);
    return 0;
}






