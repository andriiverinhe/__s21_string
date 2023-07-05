#include "s21_string.h"

size_t s21_strspn(const char *str1, const char *str2) {
    size_t len = 0;
    const char *ptr1, *ptr2;
    int err = 1;
    if(str1 && str2) {
    err = 0;
    ptr1 = str1;
    ptr2 = str2;
    }
    for (; !err && *ptr2 && *ptr1; ptr1++) {
        while (*ptr2 && *ptr1 != *ptr2)
            ptr2++;   

        if (*ptr2) 
            len++;
        
    }
    return err? -1 : len;
}