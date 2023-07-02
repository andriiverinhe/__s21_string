#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helpers/get_len.h"

char* s21_strpbrk(char *str, char *sym ) {
    int str_len = get_len(str);
    int sym_len = get_len(sym);
    int check_flag = 0;
    char *p = NULL;

    for (int i = 0; i < str_len && !check_flag; i++) {
        for (int j = 0; j < sym_len; j++) {
            if (str[i] == sym[j]) {
                p = &str[i];
                check_flag = 1;
                break;
            }
        }
    }
    return p;
}