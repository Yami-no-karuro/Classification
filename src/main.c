#include <stdio.h>
#include "lib/string_utils.h"
#include "lib/tokenizer.h"

int main() 
{
    char *input = "Naive Bayes is a simple technique for constructing classifiers: models that assign class labels to problem instances, represented as vectors of feature values, where the class labels are drawn from some finite set.";
    int token_count = 0;

    Token *tokens = tokenize(input, &token_count);
    if (!tokens) {
        printf("Errore nella tokenizzazione.\n");
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
            case TOKEN_SYMBOL:
                printf("SYMBOL\n");
                break;
            default:
                printf("UNKNOWN\n");
        }
    }

    free_tokens(tokens, token_count);
    return 0;
}
