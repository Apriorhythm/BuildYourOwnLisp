/*
 *介绍预编译
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//#ifdef _WIN32
#ifdef __CYGWIN__
#include <string.h>

static char buffer[2048];
char* readline(char* prompt)
{
    fputs(prompt, stdout);
    // fgets读取\n并默认在最后插入\0
    fgets(buffer, 2048, stdin);
    // strlen以\0为分隔，包含\n
    char* cpy = malloc(strlen(buffer)+1);
    // strcpy以\0为分隔，会复制\n
    strcpy(cpy, buffer);
    // 消除\0同时设置字符串结束符\0
    cpy[strlen(cpy)-1] = '\0';
    return cpy;
}

/* 我的版本
 * 缺点：消耗内存

char buffer[2048];
char* readline(char* prompt)
{
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    buffer[strlen(buffer) - 1] = '\0';
    char * p = buffer;

    return p;
}
*/

void add_history(char* unused) { }

#else

#include <editline/readline.h>
//#include <editline/history.h>

#endif

int main(int agrc, char** agrv)
{
    puts("ALisp Version 0.0.0.0.1");
    puts("Press Ctrl+C to Exit\n");

    while (true)
    {
        char* input = readline("alisp>");
        add_history(input);
        printf("You said: %s\n", input);
        free(input);
        /* 我的版本
         *  //free(input);
         */
    }

    return 0;

}
