#ifndef AST_INCLUDED
#define AST_INCLUDED

#include "../include/token.h"

typedef enum enum_ast_type
{
    AST_NONE=0,
    AST_INTEGER,
    AST_REAL,
    AST_VAR,
    AST_CALL,
}AstType;

// el AST se libera antes que el lexer porque sus tokens apuntan a raw_code
struct st_ast_node
{
    AstType type;
    Token token;

    union union_ast_node_val
    {
        struct st_ast_integer
        {
            Word value;
        }integer;

        struct st_ast_real
        {
            double value;
        }real;

        struct st_ast_binary_op //Operacion binaria
        {
            //el token del nodo tiene el operador
            struct st_ast_node *operand1, *operand2; //Operandos

        }binary_op;

        struct st_ast_unary_op
        {
            struct st_ast_node *operand1;
        }unary_op;

    }value;
    
};

typedef struct st_ast_node AstNode;

Word convert_to_word(Token token);
double convert_to_double(Token token);

AstNode* new_ast_node_literal(AstType type, Token token);

#endif