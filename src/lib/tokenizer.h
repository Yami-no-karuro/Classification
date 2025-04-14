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

int get_token_type(const char *str);
Token *tokenize(const char *input, int *token_count);
void free_tokens(Token *tokens, int token_count);

#endif
