#include "s21_sprintf.h"

bool (*specifier_funcs[])(char *, arg_info *, va_list) = {
    specifier_c, specifier_s, specifier_i_or_d, specifier_i_or_d, specifier_u,
    specifier_x, specifier_X, specifier_o,      specifier_p,      specifier_f,
    specifier_e, specifier_E, specifier_g,      specifier_G,      specifier_n};

int s21_sprintf(char *str, char *format, ...) {
  va_list args;
  va_start(args, format);
  int i = 0;
  memset(str, 0, strlen(str));
  bool error = false;
  while (*format != '\0') {
    if (*format == '%') {
      format++;

      arg_info s_arg_info = give_flag_struct();
      int func_ind;
      format = parse_format_arg(&s_arg_info, args, format, &func_ind);
      if (format != NULL) {
        // if format not NULL it is safe to pass args to utility functions
        error = (*specifier_funcs[func_ind])(str, &s_arg_info, args);
        while (str[i] != '\0') i++;
      } else {
        error = true;
      }
      if (s_arg_info.precision) free(s_arg_info.precision);
      if (s_arg_info.width) free(s_arg_info.width);
      if (error) {
        str[s_arg_info.null_char] = '\0';
        break;
      }
      format++;
    } else {
      str[i++] = *format++;
    }
  }

  va_end(args);
  return 0;
}
