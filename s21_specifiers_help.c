#include "s21_sprintf.h"

// STRING PROCESSING
bool wstr_to_str(char *str_out, wchar_t *wchstr, arg_info s_arg_inf) {
  int error = false;
  int w_str_s = wstr_len(wchstr);
  if (w_str_s) {
    char *temp = calloc(w_str_s + 1, sizeof(char));
    int ind = 0;
    while (*wchstr != '\0') {
      ind += s21_wctomb(temp + ind, *wchstr++);
      if (!ind) {
        error = true;
        break;
      }
    }
    if (s_arg_inf.precision) {
      if (*s_arg_inf.precision < w_str_s) temp[*s_arg_inf.precision] = '\0';
    }
    add_width_to_out(str_out, temp, s_arg_inf);
    free(temp);
  }
  return error;
}

void str_to_str(char *str_out, char *str_arg, arg_info s_arg_inf) {
  int str_arg_len = strlen(str_arg) + size_out(s_arg_inf);
  if (str_arg_len) {
    // literals are unsafe to change
    char *temp = calloc(str_arg_len + 1, sizeof(char));
    strcpy(temp, str_arg);
    if (s_arg_inf.precision) {
      if (*s_arg_inf.precision < str_arg_len)
        temp[(*s_arg_inf.precision)] = '\0';
    }
    add_width_to_out(str_out, temp, s_arg_inf);
    free(temp);
  }
}

bool wchar_to_str(char *str_out, wchar_t ch, arg_info *s_arg_inf) {
  bool error = false;
  char *temp = calloc(2, 1);
  if (!s21_wctomb(temp, ch)) error = true;

  if (!error) add_width_to_out(str_out, temp, *s_arg_inf);
  free(temp);
  return error;
}

bool char_to_str(char *str_out, char ch, arg_info *s_arg_inf) {
  char *temp = calloc(2, 1);
  temp[0] = ch;
  add_width_to_out(str_out, temp, *s_arg_inf);
  free(temp);
  if (!(int)ch) {
    s_arg_inf->null_char = strlen(str_out);
    return true;
  }
  return false;
}

int s21_wctomb(char *dest, wchar_t wc) {
  if (wc < 0x80) {
    *dest = (char)wc;
    return 1;
  }
  return 0;
}

int wstr_len(wchar_t *str) {
  int len = 0;
  while (*str++ != '\0') len++;
  return len;
}
// END STRING

// START S AND U INT
/*******************************************************************/
bool get_u_arg(char *str_out, arg_info s_arg_inf, va_list va_list, char spc) {
  arg_u arg_u;
  bool error = false;

  if (s_arg_inf.ll) {
    arg_u = va_arg(va_list, long long unsigned int);
    if (arg_u <= ULONG_MAX) {
      printf(
          "The function expects long long unsigned int, but the value is "
          "smaller\n");
      error = true;
    }
  } else if (s_arg_inf.l) {
    arg_u = va_arg(va_list, long unsigned int);
    if (arg_u > ULONG_MAX || (arg_u <= UINT_MAX)) {
      printf(
          "The function expects long unsigned int, but the value is of other "
          "type\n");
      error = true;
    }
  } else if (s_arg_inf.h) {
    // воспроизвести overflow состояние оригинальной функции
    short unsigned sh = va_arg(va_list, unsigned int);
    arg_u = sh;
  } else {
    arg_u = va_arg(va_list, unsigned int);
    if (arg_u > UINT_MAX) {
      printf(
          "The function expects long unsigned int, but the value is of other "
          "type\n");
      error = true;
    }
  }
  if (!error) process_u_int(str_out, arg_u, s_arg_inf, spc);
  return error;
}

void process_int(char *str_out, arg_int s, arg_info s_arg_inf) {
  int str_size = size_out(s_arg_inf);
  char *str_nosign = calloc(str_size, sizeof(char));
  char *str_res = calloc(str_size, sizeof(char));

  if (s_arg_inf.precision) {
    int_to_str(s, str_nosign, *s_arg_inf.precision);
    add_sign(str_res, s, s_arg_inf);
  } else if (s_arg_inf.width) {
    if (add_sign(str_res, s, s_arg_inf))
      *s_arg_inf.width = *s_arg_inf.width - 1;
    int_to_str(s, str_nosign, ((s_arg_inf.zeros) ? *s_arg_inf.width : 1));
  } else {
    int_to_str(s, str_nosign, 1);
  }
  strcat(str_res, str_nosign);
  add_width_to_out(str_out, str_res, s_arg_inf);

  free(str_res);
  free(str_nosign);
}

void process_u_int(char *str_out, arg_u u, arg_info s_arg_inf, char den) {
  int str_size = size_out(s_arg_inf);
  char *str_res = calloc(str_size, sizeof(char));
  if (s_arg_inf.hash && u != 0) {
    if (s_arg_inf.precision) {
      if (den == 'o') *s_arg_inf.precision = *s_arg_inf.precision - 1;
      if (den == 'x' || den == 'X')
        *s_arg_inf.precision = *s_arg_inf.precision - 2;
    }
    if (s_arg_inf.width && s_arg_inf.zeros) {
      if (den == 'o') *s_arg_inf.width = *s_arg_inf.width - 1;
      if (den == 'x' || den == 'X') *s_arg_inf.width = *s_arg_inf.width - 2;
    }
  }
  if (s_arg_inf.precision)
    u_int_to_str(u, str_res, *s_arg_inf.precision, den, s_arg_inf);
  else if (s_arg_inf.width && s_arg_inf.zeros)
    u_int_to_str(u, str_res, *s_arg_inf.width, den, s_arg_inf);
  else
    u_int_to_str(u, str_res, 1, den, s_arg_inf);
  add_width_to_out(str_out, str_res, s_arg_inf);
  free(str_res);
}

int int_to_str(arg_int x, char *str, int d) {
  int i = 0;
  arg_int xp = arg_abs(x);
  while (xp) {
    str[i++] = (xp % 10) + '0';
    xp = xp / 10;
  }
  while (i < d) str[i++] = '0';
  reverse(str, i);
  str[i] = '\0';
  return i;
}

int u_int_to_str(arg_u x, char *str, int z, char den, arg_info s) {
  int d;
  if (den == 'u') d = 10;
  if (den == 'o') d = 8;
  if (den == 'x' || den == 'X') d = 16;

  int i = 0;
  int saved = x;
  if (d <= 10) {
    while (x) {
      str[i++] = (x % d) + '0';
      x = x / d;
    }
  } else {
    while (x) {
      int temp = x % d;
      if (temp < 10)
        temp += 48;
      else
        temp += ((den == 'x') ? 87 : 55);
      str[i++] = temp;
      x = x / d;
    }
  }
  while (i < z) str[i++] = '0';
  if (s.hash && saved != 0) {
    if (den == 'x' || den == 'X') str[i++] = den;
    str[i++] = '0';
  }
  reverse(str, i);
  str[i] = '\0';
  return i;
}

void reverse(char *str, int len) {
  int i = 0, j = len - 1, temp;
  while (i < j) {
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
    i++;
    j--;
  }
}

bool add_sign(char *str, arg_int x, arg_info s_arg_inf) {
  bool res = false;
  if (s_arg_inf.plus && x > 0) {
    str[0] = '+';
    res = true;
  }
  if (s_arg_inf.space && x > 0) {
    str[0] = ' ';
    res = true;
  }
  if (x < 0) {
    str[0] = '-';
    res = true;
  }
  return res;
}

arg_int arg_abs(arg_int x) {
  if (x < 0) return x * (-1);
  return x;
}
// END INT

// START DOUBLE
/*******************************************************************/
void process_ldouble(char *str_out, ld arg_ld, arg_info s_arg_inf) {
  int res_size = size_out(s_arg_inf);
  char *res = calloc(res_size, sizeof(char));

  lftoa(arg_ld, res, res_size,
        ((s_arg_inf.precision) ? *s_arg_inf.precision : 6), s_arg_inf);
  add_width_to_out(str_out, res, s_arg_inf);
  free(res);
}

void process_double(char *str_out, double arg_d, arg_info s_arg_inf) {
  int res_size = size_out(s_arg_inf);
  char *res = calloc(res_size, sizeof(char));

  ftoa(arg_d, res, res_size, ((s_arg_inf.precision) ? *s_arg_inf.precision : 6),
       s_arg_inf);
  add_width_to_out(str_out, res, s_arg_inf);
  free(res);
}

void lftoa(ld n, char *res, int r_size, int afterpoint, arg_info s_arg_inf) {
  arg_int ipart = (arg_int)n;
  ld fpart = n - (ld)ipart;
  int i = int_to_str(ipart, res, 0);
  if (!i) res[i++] = '0';
  if (s_arg_inf.hash) res[i] = '.';
  if (afterpoint != 0) {
    res[i] = '.';
    fpart = fpart * pow(10, afterpoint);

    int_to_str((arg_int)fpart, res + i + 1, afterpoint);
  }
  char *signedres = calloc(r_size, sizeof(char));
  int comp = (!n) ? 0 : ((n > 0) ? 1 : -1);
  int sign = add_sign(signedres, comp, s_arg_inf);
  if (s_arg_inf.width && s_arg_inf.zeros) {
    int real_w = *s_arg_inf.width - strlen(res) - sign;
    memset(signedres + sign, '0', real_w);
  }
  strcat(signedres, res);
  strcpy(res, signedres);
  free(signedres);
}

void ftoa(double n, char *res, int r_size, int afterpoint, arg_info s_arg_inf) {
  arg_int ipart = (arg_int)n;
  double fpart = n - (double)ipart;
  int i = int_to_str(ipart, res, 0);
  if (!i) res[i++] = '0';
  if (s_arg_inf.hash) res[i] = '.';
  if (afterpoint != 0) {
    res[i] = '.';
    fpart = fpart * pow(10, afterpoint);
    int_to_str((arg_int)fpart, res + i + 1, afterpoint);
  }
  char *signedres = calloc(r_size, sizeof(char));
  int comp = (!n) ? 0 : ((n > 0) ? 1 : -1);
  int sign = add_sign(signedres, comp, s_arg_inf);
  if (s_arg_inf.width && s_arg_inf.zeros) {
    int real_w = *s_arg_inf.width - strlen(res) - sign;
    memset(signedres + sign, '0', real_w);
  }
  strcat(signedres, res);
  strcpy(res, signedres);
  free(signedres);
}
// SCIENTIFIC NOTATION //
/*******************************************************************/
bool get_eg_arg(char *str_out, arg_info s_arg_inf, va_list va_list, char e) {
  bool error = false;
  if (s_arg_inf.L) {
    ld arg_ld = va_arg(va_list, long double);
    if (isnanf(arg_ld)) {
      error = true;
    }
    if (!error) {
      if (e == 'e' || e == 'E') process_e(str_out, 0, arg_ld, s_arg_inf, e);
    }
  } else {
    double arg_d = va_arg(va_list, double);
    if (isnanf(arg_d)) {
      error = true;
    }
    if (!error) {
      if (e == 'e' || e == 'E')
        process_e(str_out, 0, arg_d, s_arg_inf, e);
      else
        process_g(str_out, arg_d, s_arg_inf, (int)e - 2);
    }
  }
  return error;
}

void prep_e_dbl(double arg_d, int res_size, char *res, int adj,
                arg_info s_arg) {
  arg_d = arg_d * pow(10, adj);
  arg_int r = (arg_int)round(arg_d) % 10;
  arg_d = round(arg_d) / pow(10, adj);
  ftoa(arg_d, res, res_size, adj, s_arg);
  int i = strlen(res);
  if (res[i - 1] != '.') {
    // поправка на потерю точности после деления double
    res[i - 1] = r + '0';
  }
}

void prep_e_ldbl(ld arg_ld, int res_size, char *res, int adj, arg_info s_arg) {
  arg_ld = arg_ld * pow(10, adj);
  arg_ld = round(arg_ld) / pow(10, adj);
  ftoa(arg_ld, res, res_size, adj, s_arg);
}

void process_e(char *str_out, double arg_d, ld arg_ld, arg_info s_arg_inf,
               char e) {
  int off = (s_arg_inf.L) ? offset_le(&arg_ld) : offset_e(&arg_d);
  int res_size = size_out(s_arg_inf);
  int postfix = 4;
  char *res = calloc(res_size, sizeof(char));
  if (s_arg_inf.width) *s_arg_inf.width = *s_arg_inf.width - postfix;
  int adj = ((s_arg_inf.precision) ? *s_arg_inf.precision : 6);
  if (s_arg_inf.L) {
    prep_e_ldbl(arg_ld, res_size, res, adj, s_arg_inf);
  } else {
    prep_e_dbl(arg_d, res_size, res, adj, s_arg_inf);
  }
  add_postfix(res, off, e);
  add_width_to_out(str_out, res, s_arg_inf);
  free(res);
}

int offset_e(double *n) {
  int off = 0;
  double res = *n;
  if ((int)res != 0) {
    while ((int)res / 10 != 0) {
      res /= 10;
      off++;
    }
    // компенсируем потерю точности double при делении
    *n = *n / pow(10, off);
  } else {
    while (!(int)res) {
      res *= 10;
      off--;
    }
    *n = *n * pow(10, abs(off));
  }
  return off;
}

int offset_le(ld *n) {
  int off = 0;
  ld res = *n;
  if ((int)res != 0) {
    while ((int)res / 10 != 0) {
      res /= 10;
      off++;
    }
  } else {
    while (!(int)res) {
      res *= 10;
      off--;
    }
  }
  *n = res;
  return off;
}

void add_postfix(char *str_res, int offset, char e) {
  char post[6] = "";
  post[0] = e;
  post[1] = '+';
  if (offset < 0) post[1] = '-';
  int_to_str((arg_int)offset, post + 2, 2);
  strcat(str_res, post);
}

void remove_zeroes(char *res, arg_info s_arg) {
  int z = 0;
  for (size_t i = 0, s = 0; res[i] != '\0'; i++) {
    if (res[i] == '.') s = 1;
    if (z && res[i] != '0') z = 0;
    if (res[i] == '0' && s && !z) z = i;
  }
  if (z) {
    res[z] = '\0';
    if (res[z - 1] == '.' && !s_arg.hash) res[z - 1] = '\0';
  }
}

void prep_gedbl(int off, double arg_d, int r_size, char *res, int adj,
                arg_info s_arg, char e) {
  int postfix = 4;
  if (adj) adj--;
  if (s_arg.width) *s_arg.width = *s_arg.width - postfix;
  prep_e_dbl(arg_d, r_size, res, adj, s_arg);
  remove_zeroes(res, s_arg);
  add_postfix(res, off, e);
}

void process_g(char *str_out, double arg_d, arg_info s_arg_inf, char e) {
  int res_size = size_out(s_arg_inf);
  char *dbl_str = calloc(res_size, sizeof(char));
  double copy_d = arg_d;
  int offset = offset_e(&copy_d);
  int adj = ((s_arg_inf.precision) ? *s_arg_inf.precision : 6);
  if (offset < 0) {
    if (offset > -5) {
      prep_e_dbl(arg_d, res_size, dbl_str, adj + abs(offset) - 1, s_arg_inf);
      remove_zeroes(dbl_str, s_arg_inf);
    } else {
      prep_gedbl(offset, copy_d, res_size, dbl_str, adj, s_arg_inf, e);
    }
  } else {
    if (offset + 1 > adj) {
      prep_gedbl(offset, copy_d, res_size, dbl_str, adj, s_arg_inf, e);
    } else {
      prep_e_dbl(arg_d, res_size, dbl_str, adj - (offset + 1), s_arg_inf);
      remove_zeroes(dbl_str, s_arg_inf);
    }
  }
  add_width_to_out(str_out, dbl_str, s_arg_inf);
  free(dbl_str);
}

void add_width_to_out(char *str_out, char *temp, arg_info s_arg_inf) {
  bool added = false;

  if (s_arg_inf.width) {
    int shift = *s_arg_inf.width - strlen(temp);
    if (s_arg_inf.minus && shift > 0) {
      strcat(str_out, temp);
      int out_len = strlen(str_out) + (temp[0] == '\0');
      memset(str_out + out_len, ' ', shift);
      added = true;
    } else if (shift > 0) {
      int out_len = strlen(str_out);
      memset(str_out + out_len, ' ', shift);
      strcat(str_out, temp);
      added = true;
    }
  }
  if (!added) strcat(str_out, temp);
}

int size_out(arg_info s_arg_inf) {
  int str_size = NUM_STR;
  if (s_arg_inf.precision) str_size += *s_arg_inf.precision;
  if (s_arg_inf.width) str_size += *s_arg_inf.width;
  return str_size;
}