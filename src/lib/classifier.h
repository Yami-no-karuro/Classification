#ifndef CLASSIFIER_H
#define CLASSIFIER_H

typedef enum {
    CLASS_SPAM,
    CLASS_HAM
} MailClass;

typedef struct {
    HashTable *spam_counts;
    HashTable *ham_counts;
    int spam_total_words;
    int ham_total_words;
} Classifier;

Classifier *cls_create();
void cls_train(Classifier *c, const char *text, MailClass label);
MailClass cls_predict(Classifier *c, const char *text);
void cls_free(Classifier *c);

void cls_accumulate(const char *key, int value, void *user_data);

#endif
