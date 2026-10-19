#include "../include/token.h"


void init_token(Token* token, TokenType type, char* begin_word, Half len)
{
    if(token)
    {
        token->begin_word=begin_word;
        token->type = type;
        token->len =len;
    }

}
