#ifndef PARSER_INCLUDED
#define PARSER_INCLUDED

#include "../include/lexer.h"
#include "../include/ast.h"

struct st_parser
{
    // el parser es dueno del AST y del lexer.
    // free_parser libera el AST antes del lexer.
    Lexer lexer;
    AstNode* ast_root;


};

typedef struct st_parser Parser;

void init_parser(Parser* parser, const char* code_filename);
void free_parser(Parser* parser);

Byte check_current_token(Parser* parser, TokenType expected_type);
Byte check_previous_token(Parser* parser, TokenType expected_type);

void match_current_token(Parser* parser, TokenType expected_type);

void parse_expression(Parser* parser);
void parse_primary(Parser* parser);
void parse_unary(Parser* parser);
void parse_factor(Parser* parser);
void parse_term(Parser* parser);

#endif