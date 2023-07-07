#include "s21_sprintf.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

arg_info give_flag_struct() {
  arg_info s_arg_info = {.precision = NULL,
                         .width = NULL,
                         .plus = false,
                         .minus = false,
                         .space = false,
                         .zeros = false,
                         .hash = false,
                         .h = false,
                         .l = false,
                         .L = false};
  return s_arg_info;
}

int is_valid_specifier(char ch_now) {
  int specifier = -1;
  int i = -1;
  while (valid_specifiers[++i] != '\0') {
    if (valid_specifiers[i] == ch_now) {
      specifier = i;
      break;
    }
  }
  return specifier;
}

bool is_symbol_forbidden(char ch_now) {
  int i = -1;
  while (allowed_chars[++i] != '\0') {
    if (ch_now == allowed_chars[i])
      return false;
  }
  return true;
}

bool are_we_far_in_format(arg_info *s_arg_inf) {
  if (s_arg_inf->precision != NULL || s_arg_inf->width != NULL ||
      s_arg_inf->l || s_arg_inf->L || s_arg_inf->h)
    return true;
  return false;
}

bool is_space(char ch_now, arg_info *s_arg_inf, bool pr, bool wd) {
  if (ch_now == ' ') {
    if (s_arg_inf->plus || are_we_far_in_format(s_arg_inf) ||
        s_arg_inf->space || pr || wd)
      return true;
    s_arg_inf->space = true;
  }
  return false;
}

bool is_plus(char ch_now, arg_info *s_arg_inf, bool pr, bool wd) {
  if (ch_now == '+') {
    s_arg_inf->space = false;
    if (s_arg_inf->plus || are_we_far_in_format(s_arg_inf) || pr || wd)
      return true;
    s_arg_inf->plus = true;
  }
  return false;
}

bool is_minus(char ch_now, arg_info *s_arg_inf, bool pr, bool wd) {
  if (ch_now == '-') {
    s_arg_inf->zeros = false;
    if (s_arg_inf->minus || are_we_far_in_format(s_arg_inf) || pr || wd)
      return true;
    s_arg_inf->minus = true;
  }
  return false;
}

bool is_zero(char ch_now, arg_info *s_arg_inf, bool pr, bool wd, bool ap,
             bool aw) {
  if (ch_now == '0') {
    if ((aw && !pr) || ap)
      return true;
    if (pr) {
      int z = 0;
      if (s_arg_inf->precision == NULL) {
        s_arg_inf->precision = malloc(sizeof(int));
        *s_arg_inf->precision = z;
      } else
        *s_arg_inf->precision = (*s_arg_inf->precision) * 10;
    } else if (wd)
      *s_arg_inf->width = (*s_arg_inf->width) * 10;
    else {
      if (s_arg_inf->zeros || s_arg_inf->minus ||
          are_we_far_in_format(s_arg_inf))
        return true;
      s_arg_inf->zeros = true;
    }
  }
  return false;
}

bool is_dot(char ch_now, arg_info *s_arg_inf, bool *pr, bool *wd) {
  if (ch_now == '.') {
    if (*pr || s_arg_inf->h || s_arg_inf->L || s_arg_inf->l)
      return true;
    *wd = false;
    *pr = true;
  }
  return false;
}

bool is_non_zero_num(char ch_now, arg_info *s_arg_inf, bool *pr, bool *wd,
                     bool ap, bool aw) {
  if (ch_now >= '1' && ch_now <= '9') {
    int i_ch = ch_now - '0';
    if (s_arg_inf->h || s_arg_inf->L || s_arg_inf->l || (aw && !(*pr)) || ap)
      return true;
    if (!(*wd) && !(*pr) && s_arg_inf->width == NULL)
      *wd = true;
    if (*wd) {
      if (s_arg_inf->width == NULL) {
        s_arg_inf->width = malloc(sizeof(int));
        *s_arg_inf->width = i_ch;
      } else
        *s_arg_inf->width = ((*s_arg_inf->width) * 10) + i_ch;
    }
    if (*pr) {
      if (s_arg_inf->precision == NULL) {
        s_arg_inf->precision = malloc(sizeof(int));
        *s_arg_inf->precision = i_ch;
      } else
        *s_arg_inf->precision = ((*s_arg_inf->precision) * 10) + i_ch;
    }
  }
  return false;
}

bool is_hash(char ch_now, arg_info *s_arg_inf, bool pr, bool wd) {
  if (ch_now == '#') {
    if (s_arg_inf->hash || are_we_far_in_format(s_arg_inf) || pr || wd)
      return true;
    s_arg_inf->hash = true;
  }
  return false;
}

bool is_ast(char ch_now, arg_info *s_arg_inf, va_list arg_l, bool *pr, bool wd,
            bool *ap, bool *aw) {
  if (ch_now == '*') {
    if ((*pr && s_arg_inf->precision != NULL) || wd || s_arg_inf->h ||
        s_arg_inf->l || s_arg_inf->L)
      return true;
    if (*pr) {
      *pr = false;
      *ap = true;
    } else
      *aw = true;
    int read = va_arg(arg_l, int);
    if (read) {
      if (*ap) {
        s_arg_inf->precision = malloc(sizeof(int));
        *s_arg_inf->precision = read;
      } else {
        s_arg_inf->width = malloc(sizeof(int));
        *s_arg_inf->width = read;
      }
    }
  }
  return false;
}

bool is_letter(char ch_now, arg_info *s_arg_inf, bool *pr, bool *wd) {
  if (ch_now == 'L' || ch_now == 'l' || ch_now == 'h') {
    if (s_arg_inf->h || s_arg_inf->L || s_arg_inf->l)
      return true;
    if (*pr)
      *pr = false;
    if (*wd)
      *wd = false;
    if (ch_now == 'L')
      s_arg_inf->L = true;
    if (ch_now == 'l')
      s_arg_inf->l = true;
    if (ch_now == 'h')
      s_arg_inf->h = true;
  }
  return false;
}

bool is_not_valid_combo(char spcf, arg_info *s_arg_inf) {
  if (s_arg_inf->hash && (spcf != 'o' && spcf != 'x' && spcf != 'X' &&
                          spcf != 'e' && spcf != 'E' && spcf != 'f'))
    return true;
  if (s_arg_inf->precision && spcf == 'c')
    return true;
  if (s_arg_inf->h &&
      (spcf == 'c' || spcf == 'n' || spcf == 's' || spcf == 'p'))
    return true;
  if (s_arg_inf->l && (spcf == 'n' || spcf == 'p'))
    return true;
  if (s_arg_inf->L &&
      (spcf != 'e' || spcf != 'E' || spcf != 'f' || spcf != 'g' || spcf != 'G'))
    return true;
  return false;
}

char *parse_format_arg(arg_info *s_arg_inf, va_list args, char *ch_now,
                       int *func_ind) {
  int i;
  bool append_pr = false;
  bool append_width = false;
  bool ast_pr = false;
  bool ast_wd = false;
  bool set_pr_to_zero = false;

  while ((i = is_valid_specifier(*ch_now)) == -1) {
    // any error returns true
    if (is_symbol_forbidden(*ch_now) ||
        is_letter(*ch_now, s_arg_inf, &append_pr, &append_width) ||
        is_ast(*ch_now, s_arg_inf, args, &append_pr, append_width, &ast_pr,
               &ast_wd) ||
        is_dot(*ch_now, s_arg_inf, &append_pr, &append_width) ||
        is_hash(*ch_now, s_arg_inf, append_pr, append_width) ||
        is_minus(*ch_now, s_arg_inf, append_pr, append_width) ||
        is_space(*ch_now, s_arg_inf, append_pr, append_width) ||
        is_plus(*ch_now, s_arg_inf, append_pr, append_width) ||
        is_zero(*ch_now, s_arg_inf, append_pr, append_width, ast_pr, ast_wd) ||
        is_non_zero_num(*ch_now, s_arg_inf, &append_pr, &append_width, ast_pr,
                        ast_wd))
      return (ch_now = NULL);
    if (append_pr)
      set_pr_to_zero = true;
    i++;
    ch_now++;
  }
  if (set_pr_to_zero && s_arg_inf->precision == NULL) {
    int z = 0;
    s_arg_inf->precision = malloc(sizeof(int));
    *s_arg_inf->precision = z;
  }
  *func_ind = i;
  if (is_not_valid_combo(valid_specifiers[i], s_arg_inf))
    return NULL;
  return ch_now;
}

int s21_sprintf(char *str, char *format, ...) {
  va_list args;
  va_start(args, format);

  while (*format != '\0') {
    if (*format == '%') {
      format++;

      arg_info s_arg_info = give_flag_struct();
      int func_ind;
      bool error = false;
      format = parse_format_arg(&s_arg_info, args, format, &func_ind);
      if (format != NULL) {
        // if format not NULL it is safe to pass args to utility functions
        // debugging prints
        printf("Call function from arr by index %d\n", func_ind);
        printf("STRUCT\n "
               "plus:%d\nminus:%d\nspace:%d\nzeroes:%d\nhash:%d\nh:%d\nl:%d\nL:"
               "%d\n",
               s_arg_info.plus, s_arg_info.minus, s_arg_info.space,
               s_arg_info.zeros, s_arg_info.hash, s_arg_info.h, s_arg_info.l,
               s_arg_info.L);
        if (s_arg_info.precision != NULL)
          printf("prec:%d\n", *s_arg_info.precision);
        if (s_arg_info.width != NULL)
          printf("width:%d\n", *s_arg_info.width);
        // end debugging prints
      } else {
        printf("Incorrect flag use in formatting");
        error = true;
      }
      printf("next arg: %d\n", va_arg(args, int));
      if (s_arg_info.precision != NULL)
        free(s_arg_info.precision);
      if (s_arg_info.width != NULL)
        free(s_arg_info.width);
      if (error)
        break;
      format++;
    }
    *str = *format;
    str++;
    format++;
  }

  va_end(args);
  return 0;
}

int main(void) {
  char out[100] = "";
  // char in[50];
  // scanf("%s", in);
  char in[] = "%+0*.*lf";
  s21_sprintf(out, in, 10, 15);
  printf("%s", out);
  return 0;
}