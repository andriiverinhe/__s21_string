#ifndef S21_SPRINTH
#define S21_SPRINTH

#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>


typedef struct 
{
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
  bool L;

} arg_info;

#include "s21_specifiers_help.h"
bool specifier_c(char *str_out, arg_info s_arg_inf, va_list va_list);
bool specifier_s(char *str_out, arg_info s_arg_inf, va_list va_list);

#endif