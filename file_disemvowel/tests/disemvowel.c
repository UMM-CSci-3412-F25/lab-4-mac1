#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#include "disemvowel.h"

bool is_vowel(char c) {
    char lower = tolower((unsigned char)c);
    return lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u';
}

char *disemvowel(char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = malloc(len + 1); // Allocate memory for the result
    if (result == NULL) {
        return NULL; // Memory allocation failed
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (!is_vowel(str[i])) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0'; // Null-terminate the resulting string

    return result;

     if (str == NULL) {
    return (char*) "";
}
    size_t len = strlen(str);
    char *result = malloc(len + 1); // Allocate memory for the result
    if (result == NULL) {
        return NULL; // Memory allocation failed
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (!is_vowel(str[i])) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0'; // Null-terminate the resulting string

    return result;
}


