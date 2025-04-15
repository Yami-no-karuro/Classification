#include <stdlib.h>
#include <stdio.h>

#include "hash_table.h"
#include "tokenizer.h"
#include "string_utils.h"
#include "classifier.h"

/**
 * Creates and initializes a new Naive Bayes Classifier.
 *
 * @return A pointer to the newly allocated Classifier.
 */
Classifier *cls_create() 
{
    Classifier *cls = (Classifier *)malloc(sizeof(Classifier));
    if (!cls) {
        printf("Error: Unable to allocate enough memory for classifier.\n");
        exit(EXIT_FAILURE);
    }

    cls->spam_counts = ht_create(1024);
    cls->ham_counts = ht_create(1024);
    cls->spam_total_words = 0;
    cls->ham_total_words = 0;

    return cls;
}

/**
 * Trains the classifier with a new sentence and its label (SPAM or HAM).
 *
 * @param c - The classifier instance to be trained.
 * @param text - The sentence to analyze.
 * @param label - The label associated with the sentence (SPAM or HAM).
 */
void cls_train(Classifier *c, const char *text, MailClass label) 
{
    int token_count = 0;
    Token *tokens = tk_tokenize(text, &token_count);
    if (!tokens) {
        printf("Error: Unable to allocate enough memory for the tokenization process.\n");
        return;
    }

    for (int i = 0; i < token_count; i++) {
        if (tokens[i].type != TOKEN_WORD) continue;

        HashTable *target = (label == CLASS_SPAM) ? c->spam_counts : c->ham_counts;
        int *target_total = (label == CLASS_SPAM) ? &c->spam_total_words : &c->ham_total_words;

        int count = ht_search(target, tokens[i].content);
        if (count == -1) {
            ht_insert(target, tokens[i].content, 1);
        } else {
            ht_insert(target, tokens[i].content, count + 1);
        }

        (*target_total)++;
    }

    tk_free(tokens, token_count);
}

/**
 * Frees all memory associated with the classifier.
 *
 * @param c - The classifier instance to free.
 */
void cls_free(Classifier *c) 
{
    if (!c) return;

    ht_free(c->spam_counts);
    ht_free(c->ham_counts);
    free(c);
}

