#ifndef AST_INCLUDED
#define AST_INCLUDED

#include "../include/token.h"

typedef enum enum_ast_type
{
    AST_NONE=0,
    AST_LITERAL,
    AST_IDENTIFIER,
}AstType;

// el AST se libera antes que el lexer porque sus tokens apuntan a raw_code
struct st_ast_node
{
    AstType type;

    union union_ast_node_val
    {
        struct st_ast_literal
        {
            Token token;
        }literal;

        struct st_ast_bin_op
        {
            Token token;
            struct st_ast_node *operator1, *operator2;

        }bin_op;

    }value;
    
};

typedef struct st_ast_node AstNode;

AstNode* new_ast_node(AstNode* node, AstType type);

#endif