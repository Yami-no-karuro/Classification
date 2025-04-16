# C - Classification

## Binary Classification (Naive Bayes classifier), in C

### Intro

**Classification** teaches a machine to sort things into categories.  
It learns by looking at examples with labels (like emails marked “spam”).

After learning, it can decide which category new items belong to, like identifying if a new email is spam or not.  
**Classification**, like **Linear Regression** is a type of **Supervised Learning Algorithm** that learns from the labelled datasets and maps the data points with most optimized linear functions which can be used for prediction on new datasets.
(More on [Supervised Learning](https://en.wikipedia.org/wiki/Supervised_learning), [Linear Regression](https://en.wikipedia.org/wiki/Linear_regression) and [Classification](https://en.wikipedia.org/wiki/Classification) on [Wikipedia](https://en.wikipedia.org/))

### What is this example about?

In this example we'll take a look at **Binary Classification**, the simplest form of Classification.  
We will implement a **Naive Bayes Classifier** for a simple spam filter.

For example, let's consider a scenario where we want to distinguish spam emails by their subject lines.  
By analyzing labelled data, the classifier learns the probability of certain words appearing in spam and non-spam messages.

We tokenize the subject line into individual words (features), and compute the probability of the message being spam or not spam using **Bayes' Theorem**:

$P(Spam|Words) = [P(Words|Spam) * P(Spam)] / P(Words)$

To simplify computation, we use the "naive" assumption that each word is conditionally independent given the class.  
This allows us to compute:

$P(Words|Spam) = P(w1|Spam) * P(w2|Spam) * ... * P(wn|Spam)$

The example calculates these probabilities by analyzing a small, labelled dataset and then applies the model to new inputs to determine if they are spam.  
(More on [Naive Bayes Classifier](https://en.wikipedia.org/wiki/Naive_Bayes_classifier) and [Bayes Theorem](https://en.wikipedia.org/wiki/Bayes%27_theorem) on [Wikipedia](https://en.wikipedia.org/))

### Handling Unknown Words: Laplace Smoothing

When classifying new inputs, it's common to encounter words that were not seen during training.  
To avoid assigning zero probability to such unseen words, we use **Laplace Smoothing** (also known as *add-one smoothing*).

This technique adjusts the word probabilities like so:

$P(w_i|Class) = \frac{count(w_i) + 1}{total\_words + V}$

Where:

- `count(w_i)` is the number of times word *w_i* appears in the given class.
- `total_words` is the total word count for that class.
- `V` is the vocabulary size (i.e., the number of unique words seen in training).

This ensures that no probability is ever zero, making the classifier more robust when dealing with previously unseen data.  
This helps the classifier make predictions even when the input contains new or rare words.  
(More on [Laplace Smoothing](https://en.wikipedia.org/wiki/Additive_smoothing) on [Wikipedia](https://en.wikipedia.org/))

### Libraries & Honorable mentions

This project makes extensive use of the [String-Utils](https://github.com/Yami-no-karuro/String-Utils) library for all string manipulation operations.  
For word frequency mapping during training and classification, this project relies on the [Hash-Table](https://github.com/Yami-no-karuro/Hash-Table) implementation.

### How to get things running

This project is based on the [C-Skeleton Template](https://github.com/Yami-no-karuro/C-Skeleton), please refer to the original [readme.md](https://github.com/Yami-no-karuro/C-Skeleton/blob/master/readme.md) for available commands.

### Conclusions

The **Naive Bayes classifier** provides a simple yet powerful approach for solving text classification problems like spam detection.  
By leveraging **Bayes’ Theorem** and assuming conditional independence between words, it becomes computationally efficient and easy to implement, even in C.

Using **Laplace Smoothing**, the model gracefully handles unknown words, ensuring robustness when faced with inputs not seen during training.  
Despite its simplicity, Naive Bayes often performs surprisingly well in real-world applications, especially when working with clean, tokenized text.

This example demonstrates the core ideas behind probabilistic classification, paving the way for more advanced techniques and real-world integration.
