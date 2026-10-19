#ifndef PARSER_INCLUDED
#define PARSER_INCLUDED

#include "../include/lexer.h"

struct st_parser
{
    // el parser es dueno del AST y del lexer.
    // free_parser libera el AST antes del lexer.
    Lexer lexer;

};

typedef struct st_parser Parser;

void init_parser(Parser* parser, const char* code_filename);

#endif