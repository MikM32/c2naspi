#ifndef AST_INCLUDED
#define AST_INCLUDED

#include "../include/token.h"

typedef enum enum_ast_type
{
    AST_NONE=0,
    AST_INTEGER,
    AST_REAL,
    AST_IDENTIFIER,
}AstType;

// el AST se libera antes que el lexer porque sus tokens apuntan a raw_code
struct st_ast_node
{
    AstType type;
    Token token;   // no es dueno de la memoria, apunta a raw_code

    struct st_ast_integer
    {
        
    }integer;

};

typedef struct st_ast_node AstNode;

AstNode* new_ast_node(AstNode* node, AstType type);

#endif