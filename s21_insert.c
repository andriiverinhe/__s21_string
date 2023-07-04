#include "s21_string.h"

void *insert(const char *src, const char *str, size_t start_index){
    char *new_src = NULL;
    if(src != NULL && str != NULL && start_index >= 0 && start_index <= strlen(src)){
       new_src = (char *)calloc(strlen(src) + strlen(str) + 1, sizeof(char)); 
        for(int i = 0; i < strlen(src) + strlen(str) + 1; i++)
            new_src[i] = '0';
        new_src[strlen(src) + strlen(str) + 1] = '\0';
    }
    if(new_src) {
        int count_src = 0;
        for(int i = 0; i < strlen(new_src); i++){
            if(i != start_index){
                new_src[i] = src[count_src++];
            }
            if(i == start_index){
                for(int j = 0; j < strlen(str); j++) {
                    new_src[i] = str[j];
                    if(j != strlen(str) - 1)
                        i++;
                }
            }
        }
    }
    return new_src ? (void*)new_src : NULL;
}