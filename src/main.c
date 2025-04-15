#include <stdio.h>

#include "hash_table.h"
#include "tokenizer.h"
#include "string_utils.h"
#include "classifier.h"

int main()
{
    Classifier *classifier = cls_create();

    cls_train(classifier, "Congratulations, you've won a $1000 gift card!", CLASS_SPAM);
    cls_train(classifier, "Earn money fast with this simple trick.", CLASS_SPAM);
    cls_train(classifier, "Get rich quick with our exclusive offer.", CLASS_SPAM);
    cls_train(classifier, "You have been selected for a free prize!", CLASS_SPAM);

    cls_train(classifier, "Let's schedule a meeting for next week.", CLASS_HAM);
    cls_train(classifier, "Don't forget to submit the report by Friday.", CLASS_HAM);
    cls_train(classifier, "Can you review the code before deployment?", CLASS_HAM);
    cls_train(classifier, "Lunch at 1pm sounds great, see you then.", CLASS_HAM);

    printf("Training completed on 8 examples.\n");

    cls_free(classifier);
    return 0;
}
