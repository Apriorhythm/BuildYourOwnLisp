/*
 * 语法分析
 * 构建语法解析器:波兰表达式(后缀表达式)
 * 波兰表达式的语法:
 *      Program     : the start of input, an <Operator>, one or more <Expression>, and the end of input.
 *      Expression  : either a <Number> or <(>, an <Operator>, one or more <Expression>, and an <)>.
 *      Operator    : <+>, <->, <*>, or </>.
 *      Number      : an optional <->, and one or more characters between 0 and 9
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../mpc.h"

#ifdef __CYGWIN__
#include <string.h>

static char buffer[2048];
char* readline(char* prompt)
{
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char* cpy = malloc(strlen(buffer)+1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy)-1] = '\0';
    return cpy;
}

void add_history(char* unused) { }

#else

#include <editline/readline.h>

#endif

int main(int agrc, char** agrv)
{
    /* 解析器 */
    mpc_parser_t* Number    = mpc_new("number");
    mpc_parser_t* Operator  = mpc_new("operator");
    mpc_parser_t* Expr      = mpc_new("expr");
    mpc_parser_t* ALisp     = mpc_new("alisp");

    /* 定义语言 */
    mpca_lang(MPCA_LANG_DEFAULT,
        "                                                   \
            number  : /-?[0-9]+/ ;                          \
            operator: '+' | '-' | '*' | '/';                \
            expr    : <number> | '(' <operator> <expr>+ ')';\
            alisp   : /^/ <operator> <expr>+ /$/;           \
        ",
        Number, Operator, Expr, ALisp);

    puts("ALisp Version 0.0.0.0.1");
    puts("Press Ctrl+C to Exit\n");

    while (true)
    {
        char* input = readline("alisp>");
        add_history(input);

        mpc_result_t r;
        if (mpc_parse("<stdin>", input, ALisp, &r))
        {
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        }
        else
        {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);
    }

    return 0;

}
