#include <stdio.h>
#include "../include/lexer.h"

int main()
{
    Lexer a;
    init_lexer(&a, "prueba.c");
    lex(&a);
    lex(&a);
    lex(&a);
    free_lexer(&a);
    return 0;
}