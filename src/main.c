#include <stdio.h>
#include "../include/parser.h"

int main()
{
    Parser parser;
    init_parser(&parser, "prueba.c");
    lex(&parser.lexer);
    parse_expression(&parser);

    print_ast(parser.ast_root, 1);
    return 0;
}