#ifndef S21_STRING
#define S21_STRING

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *insert(const char *src, const char *str, size_t start_index);
size_t s21_strspn(const char *str1, const char *str2);
char *s21_strtok(char *str, const char *delim);
void *trim(const char *src, const char *trim_chars);


#endif