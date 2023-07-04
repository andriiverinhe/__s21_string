#include "s21_string.h"

void find_start(size_t src_len, size_t trim_chars_len, int *i, int *j, const char *src, const char *trim_chars) {
      for ((*i) = 0; *i < src_len; (*i)++) {
      int found = 0;
      for ((*j) = 0; *j < trim_chars_len; (*j)++) {
         if (src[*i] == trim_chars[*j]) {
            found = 1;
            break;
         }
      }
      if (!found) {
         break;
      }
   }
}

void find_end(size_t src_len, size_t trim_chars_len, int *i, int *j, const char *src, const char *trim_chars) {
   for (*j = src_len - 1; *j >= *i; (*j)--) {
      int found = 0;
      for (int k = 0; k < trim_chars_len; k++) {
         if (src[*j] == trim_chars[k]) {
            found = 1;
            break;
         }
      }
      if (!found) {
         break;
      }
   }
}

void *trim(const char *src, const char *trim_chars) {

   int i, j;
   char *trimmed_str;
   int src_len = strlen(src);
   int trim_chars_len = strlen(trim_chars);

   // Find the starting index of the trimmed string
   find_start(src_len, trim_chars_len, &i, &j, src, trim_chars);

   // Find the ending index of the trimmed string
   find_end(src_len, trim_chars_len, &i, &j, src, trim_chars);

   // Allocate memory for the trimmed string
   int trimmed_len = j - i + 1;
   trimmed_str = (char *)malloc(trimmed_len + 1);

   // Copy the trimmed string into the newly allocated memory
   strncpy(trimmed_str, src + i, trimmed_len);
   trimmed_str[trimmed_len] = '\0';

   return trimmed_str;
}