#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *to_upper(char *str) {
    int i = 0;
    if (str == NULL)
      return NULL;
    size_t length = strlen(str);
    char *copy = malloc(length + 1); 
    while (str[i] != '\0') {
        if (str[i] >= 'a' && str[i] <= 'z') copy[i] = str[i] - ('a' - 'A');
        else copy[i] = str[i];
        i++;
    }
    copy[length] = '\0';
    return copy;
}

int main() {
    char str[100] = "";

    printf("Enter a string: ");
    fgets(str, 100, stdin);

    char *new = to_upper(str);

    if (new) {
      printf("Converted string: %s\n", new);
      free(new);
    } 

    return 0;
}