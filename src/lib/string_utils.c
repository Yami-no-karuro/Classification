#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "string_utils.h"

/**
 * Checks if a substring is contained within a string.
 *
 * @param subject - The original string to search within.
 * @param search - The substring to look for.
 * @return - 1 if the substring is found, 0 otherwise.
 */
int str_contains(const char *subject, const char *search)
{
    return strstr(subject, search) != NULL;
}

/**
 * Counts the number of non-overlapping occurrences of a substring within a string.
 *
 * @param subject - The original string to search within.
 * @param search - The substring to look for.
 * @return - The number of times the substring appears in the subject string.
 */
int str_count(const char *subject, const char *search)
{
    int count = 0;
    const char *pos = subject;
    while ((pos = strstr(pos, search)) != NULL) {
        count++;
        pos += strlen(search);
    }

    return count;
}

/**
 * Splits a string into tokens based on a specified delimiter.
 *
 * @param subject - The original string to split.
 * @param delimiter - The character used as the delimiter to split the string.
 * @return - A NULL-terminated array of strings (tokens).
 */
char **str_split(const char *subject, char delimiter)
{
    size_t count = 1;
    for (const char *s = subject; *s; ++s)
        if (*s == delimiter)
            count++;

    char **result = (char **)malloc((count + 1) * sizeof(char *));
    if (!result)
        return NULL;

    size_t idx = 0;
    const char *start = subject;
    for (const char *s = subject; ; ++s) {
        if (*s == delimiter || *s == '\0') {

            size_t len = s - start;
            result[idx] = (char *)malloc(len + 1);
            if (!result[idx]) {
                for (size_t j = 0; j < idx; ++j)
                    free(result[j]);

                free(result);
                return NULL;
            }

            strncpy(result[idx], start, len);
            result[idx][len] = '\0';
            idx++;

            if (*s == '\0')
                break;

            start = s + 1;
        }
    }

    result[idx] = NULL;
    return result;
}

/**
 * Joins an array of strings into a single string using the specified delimiter.
 *
 * @param strings - A NULL-terminated array of strings to join.
 * @param delimiter - The string to insert between each pair of strings.
 * @return - A newly allocated string containing the joined result.
 */
char *str_join(char **strings, const char *delimiter)
{
    size_t total_len = 0;
    size_t delim_len = strlen(delimiter);
    size_t count = 0;

    for (char **s = strings; *s; s++) {
        total_len += strlen(*s);
        count++;
    }

    total_len += (count - 1) * delim_len;
    char *result = malloc(total_len + 1);
    if (!result)
        return NULL;

    result[0] = '\0';

    for (size_t i = 0; i < count; ++i) {
        strcat(result, strings[i]);
        if (i < count - 1)
            strcat(result, delimiter);
    }

    return result;
}

/**
 * Removes leading and trailing whitespace characters from a string.
 *
 * @param subject - The original string to trim.
 * @return - The resulting string.
 */
char *str_trim(const char *subject)
{
    const char *start = subject;
    while (*start && isspace((unsigned char)*start))
        start++;

    const char *end = subject + strlen(subject) - 1;
    while (end > start && isspace((unsigned char)*end))
        end--;

    if (end < start)
        return strdup("");

    size_t trimmed_len = end - start + 1;
    char *result = (char *)malloc(trimmed_len + 1);
    if (!result)
        return NULL;

    strncpy(result, start, trimmed_len);
    result[trimmed_len] = '\0';

    return result;
}

/**
 * Removes punctuation characters from the beginning and end of a string.
 *
 * @param subject - The input string to clean.
 * @return - A newly allocated string with punctuation removed.
 */
char *str_strip_punct(const char *subject)
{
    const char *start = subject;
    while (*start && ispunct((unsigned char)*start))
        start++;

    const char *end = subject + strlen(subject) - 1;
    while (end > start && ispunct((unsigned char)*end))
        end--;

    size_t len = end - start + 1;
    char *result = (char *)malloc(len + 1);
    if (!result)
        return NULL;

    strncpy(result, start, len);
    result[len] = '\0';

    return result;
}

/**
 * Replaces the first occurrence of a substring within a string with another substring.
 *
 * @param subject - The original string in which the replacement is performed.
 * @param search - The substring to be replaced.
 * @param replace - The substring to replace the search string.
 * @return - The resulting string.
 */
char *str_replace(const char *subject, const char *search, const char *replace)
{
    char *offset = strstr(subject, search);
    if (offset == NULL)
        return NULL;

    int offset_index = offset - subject;
    int search_length = strlen(search);
    int replace_length = strlen(replace);
    int result_length = strlen(subject) - search_length + replace_length;

    char *result = (char *)malloc((result_length + 1) * sizeof(char));
    if (!result)
        return NULL;

    strncpy(result, subject, offset_index);
    strcpy(result + offset_index, replace);
    strcpy(result + offset_index + replace_length, subject + offset_index + search_length);

    return result;
}

/**
 * Replaces all occurrences of a substring within a string with another substring.
 *
 * @param subject - The original string in which the replacements are performed.
 * @param search - The substring to be replaced.
 * @param replace - The substring to replace the search string.
 * @return - The resulting string with all occurrences replaced.
 */
char *str_replace_all(const char *subject, const char *search, const char *replace)
{
    char *result = str_replace(subject, search, replace);
    if (!result)
        return NULL;
    
    char *next_result;
    while ((next_result = str_replace(result, search, replace)) != NULL) {
        free(result);
        result = next_result;
    }

    return result;
}
