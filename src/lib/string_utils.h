#ifndef STRING_UTILS_H
#define STRING_UTILS_H

int str_contains(const char *subject, const char *search);
int str_count(const char *subject, const char *search);

char **str_split(const char *subject, char delimiter);
char *str_join(char **strings, const char *delimiter);

char *str_trim(const char *subject);
char *str_replace(const char *subject, const char *search, const char *replace);
char *str_replace_all(const char *subject, const char *search, const char *replace);

#endif
