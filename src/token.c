#include "../include/token.h"


void init_token(Token* token, TokenType type, Half begin_pos, Half len)
{
    if(token)
    {
        token->begin_pos=begin_pos;
        token->type = type;
        token->len =len;
    }

}