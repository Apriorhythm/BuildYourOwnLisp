#include <stdio.h>
#include <stdbool.h>

/*
 * <stdbool.h>包含了true的定义, 不include将会报错
 */

static char input[2048];

int main(int argc, char** argv)
{
    puts("ALisp Version 0.0.0.0.1");
    puts("Press Ctrl+C to Exit\n");

    while (true)
    {
        fputs("alisp>", stdout);

        /* Read a line of user input of maximum size 2048 */
        fgets(input, 2048, stdin);

        printf("You said: %s", input);
    }

    return 0;
}

