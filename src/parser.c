#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"

void init_parser(Parser* parser, const char* code_filename)
{
    init_lexer(&parser->lexer, code_filename);
    parser->ast_root = NULL;
}

void free_parser(Parser *parser)
{
    //primero liberar el AST
    //segundo liberar el lexer
    free_lexer(&parser->lexer);
}

Byte check_current_token(Parser* parser, TokenType expected_type)
{
    if(parser->lexer.current_token.type == expected_type)
    {
        return 1;
    }

    return 0;
}

Byte check_previous_token(Parser* parser, TokenType expected_type)
{
    if(parser->lexer.previous_token.type == expected_type)
    {
        return 1;
    }

    return 0;
}

void match_current_token(Parser* parser, TokenType expected_type)
{
    if(parser->lexer.current_token.type != expected_type)
    {
        fprintf(stderr, "ParseError.\n ");
        exit(1);
    }
}

void parse_primary(Parser* parser)
{
    if(check_current_token(parser, TOKEN_INTEGER))
    {
        parser->ast_root = new_ast_node_literal(AST_INTEGER, parser->lexer.current_token);
        lex(&parser->lexer);
    }
    else if(check_current_token(parser, TOKEN_REAL))
    {
        parser->ast_root = new_ast_node_literal(AST_REAL, parser->lexer.current_token);
        lex(&parser->lexer);
    }
    else if(check_current_token(parser, TOKEN_ID))
    {
        lex(&parser->lexer);
        if(check_current_token(parser, TOKEN_OPAREN))
        {
            //========= IMPLEMENTAR PARSING DE LLAMADAS A FUNCIONES
            printf("ParsingError: El parsing de funciones no esta implementado aun.");
            exit(1);
        }
        else
        {
            parser->ast_root = new_ast_node_literal(AST_VAR, parser->lexer.previous_token);
        }
    }
    else if(check_current_token(parser, TOKEN_OPAREN))
    {
        lex(&parser->lexer);
        parse_expression(parser);

        match_current_token(parser, TOKEN_CPAREN);
        lex(&parser->lexer);
    }
}

void parse_factor(Parser *parser)
{
    parse_primary(parser);
    AstNode* operand1= parser->ast_root;
    AstNode* operand2= NULL;

    Token operation_token = parser->lexer.current_token;
    if(check_current_token(parser, TOKEN_ASTERISC) ||
        check_current_token(parser, TOKEN_SLASH))
    {
        lex(&parser->lexer);
        parse_primary(parser);
        operand2= parser->ast_root;
        parser->ast_root = new_ast_node_binop(operation_token,operand1,operand2);
    }
    else
    {
        parser->ast_root = operand1;
    }

    
}

void parse_term(Parser* parser)
{
    parse_factor(parser);
    AstNode* operand1= parser->ast_root;
    AstNode* operand2= NULL;


    Token operation_token = parser->lexer.current_token;
    if(check_current_token(parser, TOKEN_PLUS) ||
        check_current_token(parser, TOKEN_MINUS))
    {
        lex(&parser->lexer);
        parse_factor(parser);
        operand2= parser->ast_root;

        parser->ast_root = new_ast_node_binop(operation_token,operand1,operand2);
    }
    else
    {
        parser->ast_root = operand1;
    }

    
}

void parse_expression(Parser *parser)
{
    parse_term(parser);
    AstNode* operand1= parser->ast_root;

}