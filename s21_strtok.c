#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *next;
  register int ch;

  if (str == 0) {
    str = next;
  }
  do {
    if ((ch = *str++) == '\0') {
      return 0;
    }
  } while (strchr(delim, ch));
  --str;
  next = str + strcspn(str, delim);
  if (*next != 0) {
    *next++ = 0;
  }
  return str;
}