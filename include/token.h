#ifndef TOKEN_INCLUDED
#define TOKEN_INCLUDED
#include "common.h"

typedef enum enum_token_type
{
    TOKEN_NONE=0,
    TOKEN_ID,
    TOKEN_OBRACE,
    TOKEN_CBRACE,
    TOKEN_INTEGER,
    TOKEN_REAL,
    TOKEN_EQUAL,
    TOKEN_SEMICOLON,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_ASTERISC,
    TOKEN_SLASH,
    TOKEN_AMPERSAND,
    TOKEN_VBAR,
    TOKEN_END,

} TokenType;

// un token no es dueno del texto, solo apunta a raw_code del lexer
struct st_token
{
    TokenType type;
    char* begin_word;   // apunta dentro de raw_code, no reserva memoria nueva
    Half len;
};

typedef struct st_token Token;

void init_token(Token* token, TokenType type, char* begin_word, Half len);

#endif