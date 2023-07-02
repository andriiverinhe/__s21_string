int get_len(char *str) {
    int len = 0;
    char p = str[len];

    while (p != '\0') {
        len++;
        p = str[len];
    }
    return len;
}