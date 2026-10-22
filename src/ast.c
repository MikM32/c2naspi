
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/ast.h"


Word convert_to_word(Token token)
{
    char* buffer = strndup(token.begin_word, token.len+1);
    if(buffer == NULL)
    {
        fprintf(stderr, "No se pudo reservar memoria para buffer en convert_to_word(Token).\n");
        exit(1);
    }

    buffer[token.len]='\0';

    Word result = atoi(buffer);

    free(buffer);

    return result;
}

double convert_to_double(Token token)
{
    char* buffer = strndup(token.begin_word, token.len+1);
    if(buffer == NULL)
    {
        fprintf(stderr, "No se pudo reservar memoria para buffer en convert_to_word(Token).\n");
        exit(1);
    }

    double result = atof(buffer);

    free(buffer);

    return result;
}

AstNode* new_ast_node_literal(AstType type, Token token)
{
    AstNode* node = malloc(sizeof(AstNode));
    node->type = type;

    switch(type)
    {
        case AST_INTEGER:
        {
            node->value.integer.value = convert_to_word(token);
            break;
        }

        case AST_REAL:
        {
            node->value.real.value = convert_to_double(token);
            break;
        }
        default:
            break;
    }

    return node;
}