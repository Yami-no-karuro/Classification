#ifndef TOKENIZER_H
#define TOKENIZER_H

enum TokenType 
{
    TOKEN_WORD,
    TOKEN_NUMBER,
    TOKEN_SYMBOL,
    TOKEN_UNKNOWN
};

typedef struct {
    char *content;
    int type;
} Token;

int tk_get_type(const char *str);

Token *tk_whitespace_tokenize(const char *input, int *token_count);

void tk_free(Token *tokens, int token_count);

#endif
