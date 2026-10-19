#ifndef LEXER_INCLUDED
#define LEXER_INCLUDED
#include "common.h"
#include "token.h"

    struct st_lexer{
        Token current_token, previous_token;
        Half current_char_pos;
        Word code_size;
        char* raw_code;     // buffer del fuente, se libera al final de todo
        char* current_code; // cursor de lectura, apunta dentro de raw_code
        
    };

    typedef struct st_lexer Lexer;

    char* c2mada_readfile(const char* filename, Word* code_size); //Lee el codigo fuente para Linux/Windows
    void debug_lex(Lexer* lexer);
    void lex_skip_garbage(Lexer* lexer);
    void init_lexer(Lexer* lexer, const char* code_filename);
    void lex(Lexer* lexer);
    void lex_identifier(Lexer* lexer);
    void lex_num(Lexer* lexer);
    // solo free_parser deberia llamar esto, despues de liberar el AST
    void free_lexer(Lexer* lexer);

#endif
