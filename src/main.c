#include <stdio.h>
#include "../include/lexer.h"

int main()
{
    Lexer a;
    init_lexer(&a, "prueba.c");
    printf("%c", *(a.raw_code+1));
    free_lexer(&a);
    return 0;
}