#include <stdio.h>
#include "../include/parser.h"

void init_parser(Parser* parser, const char* code_filename)
{
    init_lexer(&parser->lexer, code_filename);
}
