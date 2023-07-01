#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int get_len(char *str);
char* s21_strpbrk(char *str, char *sym );

int main() {
    char *str = "qweqwefad5123";
    char *sym = "e";
    char *res = s21_strpbrk(str, sym);
    printf("%s\n", res);
    printf("%s\n", str);
    return 0;
}


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

int get_len(char *str) {
    int len = 0;
    char p = str[len];

    while (p != '\0') {
        len++;
        p = str[len];
    }
    return len;
}