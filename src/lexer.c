#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/lexer.h"

#define DEBUG_LEX


char* c2mada_readfile(const char* filename, Word* code_size)
{
    FILE* codefile = fopen(filename, "rb");
    if(!codefile) return NULL;
    
    if(fseek(codefile, 0, SEEK_END) != 0){ fclose(codefile); return NULL;}

    long size = ftell(codefile);
    rewind(codefile);
    if(size <= 0){ fclose(codefile); return NULL;}

    *code_size = size;
    
    char* raw_code = malloc((size_t)size + 1);
    if(!raw_code){ fclose(codefile); return NULL;}

    if(fread(raw_code, sizeof(char), (size_t)size, codefile) != (size_t)size)
    {
        free(raw_code);
        fclose(codefile);
        return NULL;
    }

    raw_code[size]='\0';
    fclose(codefile);

    return raw_code;
}

void init_lexer(Lexer* lexer, const char* code_filename)
{
    lexer->current_char_pos=0;
    lexer->raw_code= c2mada_readfile(code_filename, &lexer->code_size);
    lexer->current_code = lexer->raw_code;
    lexer->current_token.type=TOKEN_NONE;
    lexer->previous_token.type=TOKEN_NONE;

    if(!lexer->raw_code)
    {
        fprintf(stderr, "No se pudo leer el codigo fuente: %s\n",code_filename);
        exit(1);
    }
}

void free_lexer(Lexer* lexer)
{
    lexer->current_char_pos=0;
    free(lexer->raw_code); //AVISO: El if solo compara si la referencia al lexer no es nula pero no maneja si el raw_code fue liberado antes o es nulo 
}

void lex_next(Lexer* lexer)
{
    if(*lexer->current_code != '\0')
    {
        lexer->current_char_pos++;
        lexer->current_code++;
    }
    else {
        init_token(&lexer->current_token, TOKEN_END, lexer->current_char_pos, 0);
    }
}

void lex_num(Lexer* lexer)
{
    Byte len=0;
    Half token_pos=lexer->current_char_pos;
    TokenType type=TOKEN_INTEGER;

    while(isdigit(*lexer->current_code))
    {
        len++;
        lex_next(lexer);
    }

    if(*lexer->current_code == '.')
    {
        type=TOKEN_REAL;
        len++;
        lex_next(lexer);
        while(isdigit(*lexer->current_code))
        {
            len++;
            lex_next(lexer);
        }
    }

    init_token(&lexer->current_token, type, token_pos, len);

}

void lex_identifier(Lexer* lexer)
{
    Byte len=0;
    Half token_pos=lexer->current_char_pos;
    TokenType type=TOKEN_ID;

    while(isalnum(*lexer->current_code))
    {
        len++;
        lex_next(lexer);
    }

    init_token(&lexer->current_token, type, token_pos, len);
}

void lex_skip_garbage(Lexer* lexer)
{

    Byte still_garbage=0;

    do {
        switch(*lexer->current_code)
        {
            case '\n':
            case '\t':
            case ' ':
            case '\r':
                still_garbage=1;
                lex_next(lexer);
                break;
            default:
                still_garbage=0;
                break;
        }
    }while (still_garbage);
    
}

void lex(Lexer* lexer)
{

    lex_skip_garbage(lexer);


    if(isdigit(*lexer->current_code))
    {
        lex_num(lexer);
    }
    else if(isalpha(*lexer->current_code))
    {
        lex_identifier(lexer);
    }
    else
    {
        switch(*lexer->current_code)
        {
            case '+':{
                init_token(&lexer->current_token, TOKEN_PLUS,lexer->current_char_pos, 1);
                break;
            }
            case '-':{
                init_token(&lexer->current_token, TOKEN_MINUS,lexer->current_char_pos, 1);
                break;
            }
            case '*':{
                init_token(&lexer->current_token, TOKEN_ASTERISC,lexer->current_char_pos, 1);
                break;
            }
            case '/':{
                init_token(&lexer->current_token, TOKEN_SLASH,lexer->current_char_pos, 1);
                break;
            }
        }
        lex_next(lexer);
    }

    #ifdef DEBUG_LEX
    debug_lex(lexer);
    #endif

    lexer->previous_token= lexer->current_token;
}

void debug_lex(Lexer* lexer)
{
    switch(lexer->current_token.type)
    {
        case TOKEN_ID:{

            printf("TOKEN_ID: %.*s\n", lexer->current_token.len, lexer->raw_code+lexer->current_token.begin_pos);

            break;
        }

        case TOKEN_INTEGER:
        {
            printf("TOKEN_INTEGER: %.*s\n", lexer->current_token.len, lexer->raw_code+lexer->current_token.begin_pos);
            break;
        }
        
        case TOKEN_REAL:
        {
            printf("TOKEN_REAL: %.*s\n", lexer->current_token.len, lexer->raw_code+lexer->current_token.begin_pos);
            break;
        }

        case TOKEN_END:
        {
            printf("TOKEN_END: Fin del codigo.\n");
            break;
        }

        default:
        break;
    }
}