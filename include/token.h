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

struct st_token
{
    TokenType type;
    Half begin_pos;
    Half len;
};

typedef struct st_token Token;

void init_token(Token* token, TokenType type, Half begin_pos, Half len);

#endif