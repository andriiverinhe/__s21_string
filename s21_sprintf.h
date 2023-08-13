#ifndef S21_SPRINTH
#define S21_SPRINTH

#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <check.h>
#include <inttypes.h>

#define NUM_STR 64
typedef struct {
  // flags
  bool plus;
  bool minus;
  bool space;
  bool zeros;
  bool hash;
  // width
  int *width;
  // precision
  int *precision;
  // length
  bool h;
  bool l;
  bool ll;
  bool L;
  int null_char;

} arg_info;

typedef long long int arg_int;
typedef long long unsigned int arg_u;
typedef long double ld;
#define SHOW_ERROR false
#include "s21_specifiers_help.h"

bool specifier_c(char *str_out, arg_info *s_arg_inf, va_list va_list);
bool specifier_s(char *str_out, arg_info *s_arg_inf, va_list va_list);
bool specifier_i_or_d(char *str_out, arg_info *s_arg_inf, va_list va_list);
bool specifier_u(char *str_out, arg_info *s_arg_inf, va_list va_list);
bool specifier_x(char *str_out, arg_info *s_arg_inf, va_list va_list);
bool specifier_X(char *str_out, arg_info *s_arg_inf, va_list va_list);
bool specifier_o(char *str_out, arg_info *s_arg_inf, va_list va_list);
bool specifier_p(char *str_out, arg_info *s_arg_inf, va_list va_list);
bool specifier_f(char *str_out, arg_info *s_arg_inf, va_list va_list);
bool specifier_e(char *str_out, arg_info *s_arg_inf, va_list va_list);
bool specifier_E(char *str_out, arg_info *s_arg_inf, va_list va_list);
bool specifier_g(char *str_out, arg_info *s_arg_inf, va_list va_list);
bool specifier_G(char *str_out, arg_info *s_arg_inf, va_list va_list);
bool specifier_n(char *str_out, arg_info *s_arg_inf, va_list va_list);
arg_info give_flag_struct();
char *parse_format_arg(arg_info *s_arg_inf, va_list args, char *ch_now,
                       int *func_ind);
int s21_sprintf(char *str, char *format, ...);

#endif