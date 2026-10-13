#ifndef LEXER_INCLUDED
#define LEXER_INCLUDED
#include "common.h"
#include "token.h"

    struct st_lexer{
        Token current_token, previous_token;
        Half current_char_pos;
        char* raw_code;
        
    };

    typedef struct st_lexer Lexer;

    char* c2mada_readfile(const char* filename); //Lee el codigo fuente para Linux/Windows
    void init_lexer(Lexer* lexer, const char* code_filename);
    void free_lexer(Lexer* lexer);

#endif
