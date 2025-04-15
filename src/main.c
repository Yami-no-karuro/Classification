#include <stdio.h>

#include "lib/string_utils.h"
#include "lib/tokenizer.h"
#include "lib/hash_table.h"

void print_word_count(const char *key, int value, void *user_data) {
    printf("'%s': %d\n", key, value);
}

int main() 
{
    int token_count = 0;
    char *input = "Hi friend! It’s Brian, and I have a fantastic offer to earn extra income for your business.";

    Token *tokens = tk_tokenize(input, &token_count);
    if (!tokens) {
        printf("Error: unable to allocate enough memory for the tokenization process.\n");
        return 1;
    }

    HashTable *word_counts = ht_create(1024);
    for (int i = 0; i < token_count; i++) {
        if (!tokens[i].type == TOKEN_WORD)
            continue;

        int current_count = ht_search(word_counts, tokens[i].content);
        if (current_count == -1) {
            ht_insert(word_counts, tokens[i].content, 1);
        } else {
            ht_insert(word_counts, tokens[i].content, current_count + 1);
        }
    }

    printf("Word frequencies:\n");
    ht_foreach(word_counts, print_word_count, NULL);

    tk_free(tokens, token_count);
    ht_free(word_counts);
    return 0;
}
