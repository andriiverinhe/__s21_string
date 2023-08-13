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
  if (s_arg_inf->ll) {
    arg_int = va_arg(va_list, long long int);
  } else if (s_arg_inf->l) {
    arg_int = va_arg(va_list, long int);
  } else if (s_arg_inf->h) {
    // воспроизвести overflow состояние оригинальной функции
    short sh = va_arg(va_list, int);
    arg_int = sh;
  } else {
    arg_int = va_arg(va_list, int);
  }
  process_int(str_out, arg_int, *s_arg_inf);
  return false;
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
  if (!address)
    add_width_to_out(str_out, "(nil)", *s_arg_inf);
  else {
    s_arg_inf->hash = true;
    if (s_arg_inf->precision) (*s_arg_inf->precision) += 2;
    process_u_int(str_out, address, *s_arg_inf, 'x');
  }
  return false;
}

bool specifier_f(char *str_out, arg_info *s_arg_inf, va_list va_list) {
  if (s_arg_inf->L) {
    ld arg_d = va_arg(va_list, long double);
    if (isinfl(arg_d)) {
      add_inf(str_out, *s_arg_inf, arg_d);
    } else if (isnanl(arg_d)) {
      add_nan(str_out, *s_arg_inf, arg_d);
    } else
      process_ldouble(str_out, arg_d, *s_arg_inf);
  } else {
    double arg_d = va_arg(va_list, double);

    if (isnan(arg_d)) {
      add_nan(str_out, *s_arg_inf, arg_d);
    } else if (isinf(arg_d)) {
      add_inf(str_out, *s_arg_inf, arg_d);
    } else
      process_double(str_out, arg_d, *s_arg_inf);
  }

  return false;
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
    *arg_i = len;
  } else if (s_arg_inf->l) {
    long int *arg_i = va_arg(va_list, long int *);
    *arg_i = len;
  } else {
    int *arg_i = va_arg(va_list, int *);
    *arg_i = len;
  }
  return error;
}
