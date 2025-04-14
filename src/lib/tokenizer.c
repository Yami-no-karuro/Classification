#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "string_utils.h"
#include "tokenizer.h"

/**
 * Determines the type of a token based on its first character.
 *
 * @param str - The token string to analyze.
 * @return - One of the values defined in the TokenType enum.
 */
int tk_get_type(const char *str)
{
    if (isdigit(str[0])) return TOKEN_NUMBER;
    if (isalpha(str[0])) return TOKEN_WORD;

    return TOKEN_UNKNOWN;
}

/**
 * Splits a string into tokens separated by spaces and assigns a type to each token.
 *
 * @param input - The input string to tokenize.
 * @param token_count - A pointer to an integer that will be updated with the number of tokens.
 * @return - A dynamically allocated array of Token structs.
 */
Token *tk_tokenize(const char *input, int *token_count) 
{
    char **parts = str_split(input, ' ');
    if (!parts) 
      return NULL;

    int count = 0;
    for (char **p = parts; *p; ++p)
        count++;

    Token *tokens = malloc(count * sizeof(Token));
    if (!tokens) {
        for (int i = 0; i < count; i++)
            free(parts[i]);

        free(parts);
        return NULL;
    }

    for (int i = 0; i < count; ++i) {
        char *trimmed = str_trim(parts[i]);
        char *cleaned = str_strip_punct(trimmed);
        free(trimmed);

        if (strlen(cleaned) == 0) {
            free(cleaned);
            free(parts[i]);
            continue;
        }

        tokens[*token_count].content = cleaned;
        tokens[*token_count].type = tk_get_type(cleaned);
        (*token_count)++;

        free(parts[i]);
    }

    free(parts);
    return tokens;
}

/**
 * Frees the memory allocated for an array of Token structs.
 *
 * @param tokens - The array of tokens to free.
 * @param token_count - The number of tokens in the array.
 */
void tk_free(Token *tokens, int token_count)
{
    for (int i = 0; i < token_count; i++)
        free(tokens[i].content);

    free(tokens);
}
