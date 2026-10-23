
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
    if(node == NULL)
    {
        fprintf(stderr, "Error al reservar memoria para un nodo literal del AST.\n");
        exit(1);
    }

    node->type = type;
    node->token = token;

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

AstNode* new_ast_node_binop(Token token, AstNode* operand1, AstNode* operand2)
{
    AstNode* node = malloc(sizeof(AstNode));
    if(node == NULL)
    {
        fprintf(stderr, "Error al reservar memoria para un nodo binary_op del AST.\n");
        exit(1);
    }
    node->type = AST_BINOP;
    node->token = token;
    
    node->value.binary_op.operand1 = operand1;
    node->value.binary_op.operand2 = operand2;

    return node;
}

AstNode* new_ast_node_unop(Token token, AstNode* operand1)
{
    AstNode* node = malloc(sizeof(AstNode));
    if(node == NULL)
    {
        fprintf(stderr, "Error al reservar memoria para un nodo unary_op del AST.\n");
        exit(1);
    }
    node->type = AST_UNOP;
    node->token = token;
    
    node->value.binary_op.operand1 = operand1;

    return node;
}

void print_ast(AstNode* node, Byte level)
{
    if(node)
    {
        switch(node->type)
        {
            case AST_BINOP:
            {
                printf("%*c Binary Operation: %.*s\n", level, ' ', node->token.len, node->token.begin_word);
                print_ast(node->value.binary_op.operand1, level+2);
                print_ast(node->value.binary_op.operand2, level+2);
                break;
            }

            case AST_UNOP:
            {
                printf("%*c Unary Operation: %.*s\n", level, ' ', node->token.len, node->token.begin_word);
                print_ast(node->value.unary_op.operand1, level+2);
                break;
            }

            case AST_INTEGER:
            case AST_REAL:
            case AST_VAR:
            {
                printf("%*c Primary Value: %.*s\n", level, ' ', node->token.len, node->token.begin_word);
                break;
            }

            default:
            break;
        }
    }

}