#include "s21_sprintf.h"

bool specifier_s(char *str_out, arg_info *s_arg_inf, va_list va_list) {
  if (s_arg_inf->l) {
    wchar_t *wchar_str = va_arg(va_list, wchar_t *);
    if (wstr_to_str(str_out, wchar_str, *s_arg_inf)) return true;
  } else {
    char *str_arg = va_arg(va_list, char *);
    str_to_str(str_out, str_arg, *s_arg_inf);
  }
  return false;
}

bool specifier_c(char *str_out, arg_info *s_arg_inf, va_list va_list) {
  if (s_arg_inf->l) {
    wchar_t one_char = va_arg(va_list, wchar_t);
    return wchar_to_str(str_out, one_char, s_arg_inf);
  } else {
    char one_char = va_arg(va_list, int);
    return char_to_str(str_out, one_char, s_arg_inf);
  }
  return false;
}

bool specifier_i_or_d(char *str_out, arg_info *s_arg_inf, va_list va_list) {
  arg_int arg_int;
  bool error = false;
  if (s_arg_inf->ll) {
    arg_int = va_arg(va_list, long long int);
    if (arg_int <= LONG_MAX && arg_int >= LONG_MIN) {
      printf("The function expects long long int!\n");
      error = true;
    }
  } else if (s_arg_inf->l) {
    arg_int = va_arg(va_list, long int);
    if (arg_int > LONG_MAX || arg_int < LONG_MIN) {
      printf("The function expects long int, but long long int was given\n");
      error = true;
    }
    if (arg_int <= INT_MAX && arg_int >= INT_MIN) {
      printf("The function expects long int, but int was given\n");
      error = true;
    }
  } else if (s_arg_inf->h) {
    // воспроизвести overflow состояние оригинальной функции
    short sh = va_arg(va_list, int);
    arg_int = sh;
  } else {
    arg_int = va_arg(va_list, int);
    if (arg_int > INT_MAX || arg_int < INT_MIN) {
      printf("The function expects int!\n");
      error = true;
    }
  }
  if (!error)
    process_int(str_out, arg_int, *s_arg_inf);
  return error;
}

bool specifier_u(char *str_out, arg_info *s_arg_inf, va_list va_list) {
  return get_u_arg(str_out, *s_arg_inf, va_list, 'u');
}

bool specifier_x(char *str_out, arg_info *s_arg_inf, va_list va_list) {
  return get_u_arg(str_out, *s_arg_inf, va_list, 'x');
}

bool specifier_X(char *str_out, arg_info *s_arg_inf, va_list va_list) {
  return get_u_arg(str_out, *s_arg_inf, va_list, 'X');
}

bool specifier_o(char *str_out, arg_info *s_arg_inf, va_list va_list) {
  return get_u_arg(str_out, *s_arg_inf, va_list, 'o');
}

bool specifier_p(char *str_out, arg_info *s_arg_inf, va_list va_list) {
  uintptr_t address = va_arg(va_list, uintptr_t);
  char buffer[20];
  int len = 0;

  while (address != 0) {
    int remainder = address % 16;
    char hex_digit = (remainder < 10) ? remainder + '0' : remainder - 10 + 'a';
    buffer[len++] = hex_digit;
    address /= 16;
  }
  buffer[len++] = 'x';
  buffer[len++] = '0';
  reverse(buffer, len);
  buffer[len] = '\0';
  add_width_to_out(str_out, buffer, *s_arg_inf);
  return false;
}

bool specifier_f(char *str_out, arg_info *s_arg_inf, va_list va_list) {
  bool error = false;
  if (s_arg_inf->L) {
    ld arg_d = va_arg(va_list, long double);
    if (isnanf(arg_d)) {
      error = true;
    }
    if (!error)
      process_ldouble(str_out, arg_d, *s_arg_inf);
  } else {
    double arg_d = va_arg(va_list, double);
    if (isnanf(arg_d)) {
      error = true;
    }
    if (!error)
      process_double(str_out, arg_d, *s_arg_inf);
  }

  return error;
}

bool specifier_e(char *str_out, arg_info *s_arg_inf, va_list va_list) {
  return get_eg_arg(str_out, *s_arg_inf, va_list, 'e');
}

bool specifier_E(char *str_out, arg_info *s_arg_inf, va_list va_list) {
  return get_eg_arg(str_out, *s_arg_inf, va_list, 'E');
}

bool specifier_G(char *str_out, arg_info *s_arg_inf, va_list va_list) {
  return get_eg_arg(str_out, *s_arg_inf, va_list, 'G');
}

bool specifier_g(char *str_out, arg_info *s_arg_inf, va_list va_list) {
  return get_eg_arg(str_out, *s_arg_inf, va_list, 'g');
}

bool specifier_n(char *str_out, arg_info *s_arg_inf, va_list va_list) {
  bool error = false;
  int len = strlen(str_out);
  if (s_arg_inf->ll) {
    arg_int *arg_i = va_arg(va_list, long long int *);
    if (arg_i == NULL)
      error = true;
    else 
      *arg_i = len;
  } else if (s_arg_inf->l) {
    long int *arg_i = va_arg(va_list, long int *);
    if (arg_i == NULL)
      error = true;
    else 
      *arg_i = len;
  } else {
    int *arg_i = va_arg(va_list, int *);
    if (arg_i == NULL)
      error = true;
    else 
      *arg_i = len;
  }
  return error;
}

