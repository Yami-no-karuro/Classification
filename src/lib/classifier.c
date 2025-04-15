#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "hash_table.h"
#include "tokenizer.h"
#include "string_utils.h"
#include "classifier.h"

/**
 * Creates and initializes a new Naive Bayes Classifier.
 *
 * @return - A pointer to the newly allocated Classifier.
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
 * @param cls - The classifier instance to be trained.
 * @param text - The sentence to analyze.
 * @param label - The label associated with the sentence (SPAM or HAM).
 */
void cls_train(Classifier *cls, const char *text, MailClass label)
{
    int token_count = 0;
    Token *tokens = tk_tokenize(text, &token_count);
    if (!tokens) {
        printf("Error: Unable to allocate enough memory for the tokenization process.\n");
        return;
    }

    for (int i = 0; i < token_count; i++) {
        if (tokens[i].type != TOKEN_WORD) 
            continue;

        HashTable *target = (label == CLASS_SPAM) ? cls->spam_counts : cls->ham_counts;
        int *target_total = (label == CLASS_SPAM) ? &cls->spam_total_words : &cls->ham_total_words;

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
 * Predicts whether a given text is SPAM or HAM based on the trained classifier.
 *
 * @param c - The classifier instance.
 * @param text - The text to classify.
 * @return The predicted class (SPAM or HAM).
 */
MailClass cls_predict(Classifier *c, const char *text)
{
    int token_count = 0;
    Token *tokens = tk_tokenize(text, &token_count);
    if (!tokens) {
        printf("Error: Unable to allocate enough memory for tokenization.\n");
        return CLASS_HAM;
    }

    double log_spam_prob = 0.0;
    double log_ham_prob = 0.0;

    double total_spam_words = 0.0;
    double total_ham_words = 0.0;

    ht_foreach(c->spam_counts, (ht_callback)cls_accumulate, &total_spam_words);
    ht_foreach(c->ham_counts, (ht_callback)cls_accumulate, &total_ham_words);

    for (int i = 0; i < token_count; i++) {
        if (tokens[i].type != TOKEN_WORD) continue;

        int spam_word_count = ht_search(c->spam_counts, tokens[i].content);
        int ham_word_count = ht_search(c->ham_counts, tokens[i].content);

        if (spam_word_count == -1) 
            spam_word_count = 0;

        if (ham_word_count == -1) 
            ham_word_count = 0;

        log_spam_prob += log((spam_word_count + 1.0) / (total_spam_words + 1.0 * c->spam_counts->size));
        log_ham_prob += log((ham_word_count + 1.0) / (total_ham_words + 1.0 * c->ham_counts->size));

    }

    tk_free(tokens, token_count);
    return log_spam_prob > log_ham_prob ? CLASS_SPAM : CLASS_HAM;
}

/**
 * Frees all memory associated with the classifier.
 *
 * @param cls - The classifier instance to free.
 */
void cls_free(Classifier *cls)
{
    ht_free(cls->spam_counts);
    ht_free(cls->ham_counts);
    free(cls);
}

/**
 * Callback function for ht_foreach to accumulate word counts.
 * Used to calculate total word counts in spam and ham.
 *
 * @param key - The word (key).
 * @param value - The word count (value).
 * @param user_data - The pointer to the total word count.
 */
void cls_accumulate(const char *key, int value, void *user_data)
{
    double *total_words = (double *)user_data;
    *total_words += value;
}
