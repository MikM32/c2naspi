#include <stdio.h>
#include <stdlib.h>
#include "../include/lexer.h"


char* c2mada_readfile(const char* filename)
{
    FILE* codefile = fopen(filename, "rb");
    if(!codefile) return NULL;
    
    if(fseek(codefile, 0, SEEK_END) != 0){ fclose(codefile); return NULL;}

    long code_size = ftell(codefile);
    rewind(codefile);
    if(code_size <= 0){ fclose(codefile); return NULL;}
    
    char* raw_code = malloc((size_t)code_size + 1);
    if(!raw_code){ fclose(codefile); return NULL;}

    if(fread(raw_code, sizeof(char), (size_t)code_size, codefile) != (size_t)code_size)
    {
        free(raw_code);
        fclose(codefile);
        return NULL;
    }

    raw_code[code_size]='\0';
    fclose(codefile);

    return raw_code;
}

void init_lexer(Lexer* lexer, const char* code_filename)
{
    lexer->current_char_pos=0;
    lexer->raw_code= c2mada_readfile(code_filename);

    if(!lexer->raw_code)
    {
        fprintf(stderr, "No se pudo leer el codigo fuente: %s\n",code_filename);
        exit(1);
    }
}

void free_lexer(Lexer* lexer)
{
    if(lexer)
    {
        lexer->current_char_pos=0;
        free(lexer->raw_code); //AVISO: El if solo compara si la referencia al lexer no es nula pero no maneja si el raw_code fue liberado antes o es nulo 
    }
}

void lex(Lexer* lexer)
{
    switch(lexer->code
}