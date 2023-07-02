#include <string.h>
#include <stdio.h>
#include "../helpers/get_len.h"

char *s21_strstr(const char *strB, const char *strA) {
    int b_len = get_len(strB);
    int a_len = get_len(strA);
    char *res = NULL;

    for (int i = 0; i < b_len; i++) {
        for (int j = 0; j < a_len; j++) {
            if (strA[i] == strB[j]) {

            }
            
        }
        
    }
}