#include <stdio.h>
#include "lib/string_utils.h"
#include "lib/tokenizer.h"

int main() 
{
    int token_count = 0;
    char *input = "A Naive Bayes classifier is a probabilistic machine learning model used for classification tasks.";

    Token *tokens = tk_tokenize(input, &token_count);
    if (!tokens) {
        printf("Error: unable to allocate enough memory for the tokenization process.\n");
        return 1;
    }

    printf("Token found: %d\n", token_count);
    for (int i = 0; i < token_count; i++) {

        printf("Token %d: '%s' - Type: ", i + 1, tokens[i].content);
        switch (tokens[i].type) {
            case TOKEN_WORD:
                printf("WORD\n");
                break;
            case TOKEN_NUMBER:
                printf("NUMBER\n");
                break;
            default:
                printf("UNKNOWN\n");
        }
    }

    tk_free(tokens, token_count);
    return 0;
}
