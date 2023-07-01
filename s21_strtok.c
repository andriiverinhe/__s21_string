#include "s21_string.h"

char *s21_strtok(char *str, const char *delim){
    static char *next;

    if(str != NULL)
        next = str;
    else if(next == NULL || *next == '\0')
        return NULL;

    char *ptr_start = next;
    char *ptr_end = NULL;
    while (*next != '\0')
    {
        for(const char *ptr_del = delim; *ptr_del != '\0'; ptr_del++){
            if(*next == *ptr_del) {
                ptr_end = next;
                break;
            }
        }
        if(ptr_end != NULL){
            *ptr_end = '\0';
            next = ptr_end + 1;
            return ptr_start;
        }
        next++;
    }
    return ptr_start;    
}

int main() {
    char str[25] = "test1|test2/test3/test4";
    char del[2] = "/";
    printf("str: %s\n", str);
    char *p = s21_strtok(str, del);

    while (p != NULL)
    {
        printf("p: %s\n",p);
        printf("str: %s\n",p);
        p =  s21_strtok(NULL, del);
    }
    
    return 0;
}
