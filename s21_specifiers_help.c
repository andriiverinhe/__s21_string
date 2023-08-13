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
  bool error = false;
  temp[0] = ch;

  if (!(int)ch) {
    error = true;
    if (s_arg_inf->width) (*s_arg_inf->width)--;
  }
  add_width_to_out(str_out, temp, *s_arg_inf);
  if (error) s_arg_inf->null_char = strlen(str_out);
  free(temp);
  return error;
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

  if (s_arg_inf.ll) {
    arg_u = va_arg(va_list, long long unsigned int);
  } else if (s_arg_inf.l) {
    arg_u = va_arg(va_list, long unsigned int);
  } else if (s_arg_inf.h) {
    // воспроизвести overflow состояние оригинальной функции
    short unsigned sh = va_arg(va_list, unsigned int);
    arg_u = sh;
  } else {
    arg_u = va_arg(va_list, unsigned int);
  }
  process_u_int(str_out, arg_u, s_arg_inf, spc);
  return false;
}

void process_int(char *str_out, arg_int s, arg_info s_arg_inf) {
  int str_size = size_out(s_arg_inf);
  char *str_nosign = calloc(str_size, sizeof(char));
  char *str_res = calloc(str_size, sizeof(char));
  bool sign = add_sign(str_res, s, s_arg_inf);
  if (s_arg_inf.precision) {
    int_to_str(s, str_nosign, *s_arg_inf.precision);
  } else if (s_arg_inf.width) {
    int_to_str(s, str_nosign,
               ((s_arg_inf.zeros) ? *s_arg_inf.width - (int)sign : 1));
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
  while (x) {
    str[i++] = llabs((x % 10)) + '0';
    x = x / 10;
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
  arg_u saved = x;
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

bool add_sign(char *str, ld x, arg_info s_arg_inf) {
  bool res = false;
  if (s_arg_inf.plus && x >= 0) {
    str[0] = '+';
    res = true;
  }
  if (s_arg_inf.space && x >= 0) {
    str[0] = ' ';
    res = true;
  }
  if (x < 0) {
    str[0] = '-';
    res = true;
  }
  return res;
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

void rnddblstr(char *res, int sz, int fint) {
  int one_rem = (fint > 4);
  int ti = 0;
  sz = sz - (res[sz] == '\0');
  if (one_rem) {
    char *temp = calloc(sz + NUM_STR, sizeof(char));
    while (sz >= 0 && one_rem) {
      if (res[sz] == '.') {
        temp[ti++] = res[sz--];
        continue;
      }
      int c = (res[sz--] - '0') + one_rem;
      temp[ti++] = (c % 10) + '0';
      one_rem = (c > 9);
    }

    while (sz >= 0) temp[ti++] = res[sz--];
    if (one_rem) temp[ti++] = '1';
    reverse(temp, ti);
    strcpy(res, temp);
    free(temp);
  }
}

ld raw_ldblconv(char *res, int a, ld n, arg_info s_arg_inf) {
  arg_int ipart = (arg_int)n;
  ld fpart = fabsl(n - (ld)ipart);
  int i = int_to_str(ipart, res, 0);

  if (!i) res[i++] = '0';
  if (s_arg_inf.hash) res[i] = '.';
  if (a > 0) {
    res[i++] = '.';
    while (a--) {
      (fpart) *= 10;
      res[i++] = ((int)(fpart) + '0');
      fpart = fpart - (ld)(int)fpart;
    }
  }
  return fpart;
}

double raw_dblconv(char *res, int a, double n, arg_info s_arg_inf) {
  arg_int ipart = (arg_int)n;
  double fpart = fabs(n - (double)ipart);
  int i = int_to_str(ipart, res, 0);
  if (!i) res[i++] = '0';
  if (s_arg_inf.hash) res[i] = '.';
  if (a > 0) {
    res[i++] = '.';
    while (a--) {
      (fpart) *= 10;
      res[i++] = ((int)(fpart) + '0');
      fpart = fpart - (double)(int)fpart;
    }
  }
  return fpart;
}

void add_dblwid(ld x, int r_size, char *res, arg_info s_arg_inf) {
  char *signedres = calloc(r_size, sizeof(char));
  int sign = add_sign(signedres, x, s_arg_inf);
  if (s_arg_inf.width && s_arg_inf.zeros) {
    int real_w = *s_arg_inf.width - strlen(res) - sign;
    memset(signedres + sign, '0', ((real_w > 0) ? real_w : 0));
  }
  strcat(signedres, res);
  strcpy(res, signedres);
  free(signedres);
}

void ftoa(double n, char *res, int r_size, int afterpoint, arg_info s_arg_inf) {
  double fpart = raw_dblconv(res, afterpoint, n, s_arg_inf);
  rnddblstr(res, strlen(res), (int)(fpart * 10));
  add_dblwid(n, r_size, res, s_arg_inf);
}

void lftoa(ld n, char *res, int r_size, int afterpoint, arg_info s_arg_inf) {
  ld fpart = raw_ldblconv(res, afterpoint, n, s_arg_inf);
  rnddblstr(res, strlen(res), (int)(fpart * 10));
  add_dblwid(n, r_size, res, s_arg_inf);
}

// SCIENTIFIC NOTATION //
/*******************************************************************/
bool get_eg_arg(char *str_out, arg_info s_arg_inf, va_list va_list, char e) {
  if (s_arg_inf.L) {
    ld arg_ld = va_arg(va_list, long double);
    if (isnanl(arg_ld)) {
      add_nan(str_out, s_arg_inf, arg_ld);
    } else if (isinfl(arg_ld)) {
      add_inf(str_out, s_arg_inf, arg_ld);
    } else {
      if (e == 'e' || e == 'E')
        process_le(str_out, arg_ld, s_arg_inf, e, false);
      else
        process_g(str_out, arg_ld, s_arg_inf, (int)e - 2);
    }
  } else {
    double arg_d = va_arg(va_list, double);
    if (isnan(arg_d)) {
      add_nan(str_out, s_arg_inf, arg_d);
    } else if (isinf(arg_d)) {
      add_inf(str_out, s_arg_inf, arg_d);
    } else {
      if (e == 'e' || e == 'E')
        process_e(str_out, arg_d, s_arg_inf, e, false);
      else
        process_g(str_out, arg_d, s_arg_inf, (int)e - 2);
    }
  }
  return false;
}

bool move_p(char *str) {
  int i = 0;
  bool p = false;
  while (str[i] != '\0') {
    if (str[i] == '.') {
      p = true;
      while (i - 1 > 0) {
        str[i] = str[i - 1];
        str[i - 1] = '.';
        i--;
      }
      break;
    }
    i++;
  }
  return p;
}

bool rem_e_z(char *res, arg_info s_arg) {
  if (res[1] != '.' && res[1] != '\0') {
    if (res[2] != '\0') {
      res[2] = res[1];
    }
    res[1] = '.';
    res[strlen(res) - 1] = '\0';
    if (s_arg.hash) res[1] = '.';
    if (res[2] == '\0' && !s_arg.hash) res[1] = '\0';
    return true;
  }
  // 100 -> 1.0 || 1 || 1.
  // 10.43123 -> 1.04312
  return false;
}

int process_e(char *str_out, double arg_d, arg_info s_arg_inf, char e,
              bool rmtrzrs) {
  int off = offset_e(arg_d);
  int res_size = size_out(s_arg_inf);
  char *res = calloc(res_size, sizeof(char));
  int adj = ((s_arg_inf.precision) ? *s_arg_inf.precision : 6);
  adj = (adj < 0) ? 0 : adj;
  if (off > 0) {
    raw_dblconv(res, adj, arg_d, s_arg_inf);
    int b = adj + move_p(res) + 1;
    if (res[b] != '\0') {
      int fint = res[b] - '0';
      res[b] = '\0';
      rnddblstr(res, strlen(res), fint);
      if (rem_e_z(res, s_arg_inf)) off++;
    }
  } else {
    double fpart = raw_dblconv(res, adj, arg_d * pow(10, abs(off)), s_arg_inf);
    rnddblstr(res, strlen(res), (int)(fpart * 10));
    if (rem_e_z(res, s_arg_inf)) off++;
  }
  if (rmtrzrs) rtrzrs(res, s_arg_inf);
  add_postfix(res, off, e);
  add_dblwid(arg_d, res_size, res, s_arg_inf);
  add_width_to_out(str_out, res, s_arg_inf);
  free(res);
  return off;
}

int process_le(char *str_out, ld arg_ld, arg_info s_arg_inf, char e,
               bool rmtrzrs) {
  int off = offset_le(arg_ld);
  int res_size = size_out(s_arg_inf);
  char *res = calloc(res_size, sizeof(char));
  int adj = ((s_arg_inf.precision) ? *s_arg_inf.precision : 6);
  adj = (adj < 0) ? 0 : adj;
  if (off > 0) {
    raw_ldblconv(res, adj, arg_ld, s_arg_inf);
    bool p = move_p(res);
    int b = adj + p + 1;
    if (res[b] != '\0') {
      int fint = res[b] - '0';
      res[b] = '\0';
      rnddblstr(res, strlen(res), fint);
      if (rem_e_z(res, s_arg_inf)) off++;
    }
  } else {
    ld fpart = raw_ldblconv(res, adj, arg_ld * pow(10, abs(off)), s_arg_inf);
    rnddblstr(res, strlen(res), (arg_int)(fpart * 10));
    if (rem_e_z(res, s_arg_inf)) off++;
  }
  if (rmtrzrs) rtrzrs(res, s_arg_inf);
  add_postfix(res, off, e);
  add_dblwid(arg_ld, res_size, res, s_arg_inf);
  add_width_to_out(str_out, res, s_arg_inf);
  free(res);
  return off;
}

int offset_e(double n) {
  int off = 0;
  if (!(n)) return off;
  if ((int)n != 0) {
    while ((int)n / 10 != 0) {
      n /= 10;
      off++;
    }
  } else {
    while (!(int)n) {
      n *= 10;
      off--;
    }
  }
  return off;
}

int offset_le(ld n) {
  int off = 0;
  if (!(n)) return off;
  if ((int)n != 0) {
    while ((int)n / 10 != 0) {
      n /= 10;
      off++;
    }
  } else {
    while (!(int)n) {
      n *= 10;
      off--;
    }
  }
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

void rtrzrs(char *res, arg_info s_arg) {
  if (!s_arg.hash) {
    int z = 0;
    for (size_t i = 0, s = 0; res[i] != '\0'; i++) {
      if (res[i] == '.') s = 1;
      if (z && res[i] != '0') z = 0;
      if (res[i] == '0' && s && !z) z = i;
    }
    if (z) res[z] = '\0';
    if (z && res[z - 1] == '.') res[z - 1] = '\0';
  }
}

void gftoa(double n, char *res, int r_size, int afterpoint,
           arg_info s_arg_inf) {
  double fpart = raw_dblconv(res, afterpoint, n, s_arg_inf);
  rnddblstr(res, strlen(res), (int)(fpart * 10));
  rtrzrs(res, s_arg_inf);
  add_dblwid(n, r_size, res, s_arg_inf);
}

void lgftoa(ld n, char *res, int r_size, int afterpoint, arg_info s_arg_inf) {
  ld fpart = raw_ldblconv(res, afterpoint, n, s_arg_inf);
  rnddblstr(res, strlen(res), (arg_int)(fpart * 10));
  rtrzrs(res, s_arg_inf);
  add_dblwid(n, r_size, res, s_arg_inf);
}

void process_g(char *str_out, double arg_d, arg_info s_arg_inf, char e) {
  int res_size = size_out(s_arg_inf);
  char *res_str = calloc(res_size, sizeof(char));
  int adj = ((s_arg_inf.precision) ? *s_arg_inf.precision : 6);
  if (!s_arg_inf.precision) {
    int s = 6;
    s_arg_inf.precision = &s;
  }
  (*s_arg_inf.precision)--;
  int offset = process_e(res_str, arg_d, s_arg_inf, e, true);
  if (offset < 0) {
    if (offset > -5) {
      memset(res_str, '\0', strlen(res_str));
      gftoa(arg_d, res_str, res_size, (adj + (abs(offset) - (adj != 0))),
            s_arg_inf);
    }
  } else {
    if (offset < adj || (!offset && !adj)) {
      memset(res_str, '\0', strlen(res_str));
      gftoa(arg_d, res_str, res_size, (adj - (abs(offset) + (adj != 0))),
            s_arg_inf);
    }
  }
  add_width_to_out(str_out, res_str, s_arg_inf);
  free(res_str);
}

void process_lg(char *str_out, ld arg_ld, arg_info s_arg_inf, char e) {
  int res_size = size_out(s_arg_inf);
  char *res_str = calloc(res_size, sizeof(char));
  int adj = ((s_arg_inf.precision) ? *s_arg_inf.precision : 6);
  if (!s_arg_inf.precision) {
    int s = 6;
    s_arg_inf.precision = &s;
  }
  (*s_arg_inf.precision)--;
  int offset = process_le(res_str, arg_ld, s_arg_inf, e, true);
  if (offset < 0) {
    if (offset > -5) {
      memset(res_str, '\0', strlen(res_str));
      lgftoa(arg_ld, res_str, res_size, (adj + (abs(offset) - (adj != 0))),
             s_arg_inf);
    }
  } else {
    if (offset < adj || (!offset && !adj)) {
      memset(res_str, '\0', strlen(res_str));
      lgftoa(arg_ld, res_str, res_size, (adj - (abs(offset) + (adj != 0))),
             s_arg_inf);
    }
  }
  add_width_to_out(str_out, res_str, s_arg_inf);
  free(res_str);
}

void add_width_to_out(char *str_out, char *temp, arg_info s_arg_inf) {
  bool added = false;
  if (s_arg_inf.width) {
    int shift = *s_arg_inf.width - strlen(temp);
    if (s_arg_inf.minus && shift > 0) {
      strcat(str_out, temp);
      int out_len = strlen(str_out);
      if (!(temp[0] == '\0')) {
        memset(str_out + out_len, ' ', shift);
        str_out[out_len + shift] = '\0';
      }
      added = true;
    } else if (shift > 0) {
      int out_len = strlen(str_out);
      memset(str_out + out_len, ' ', shift);
      str_out[out_len + shift] = '\0';
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

void add_nan(char *str, arg_info s_arg_inf, ld x) {
  x = 1;
  char n[] = "nan";
  char s[10] = "";
  add_sign(s, x, s_arg_inf);
  strcat(s, n);
  add_width_to_out(str, s, s_arg_inf);
}

void add_inf(char *str, arg_info s_arg_inf, ld x) {
  char n[] = "inf";
  char s[10] = "";
  add_sign(s, x, s_arg_inf);
  strcat(s, n);
  add_width_to_out(str, s, s_arg_inf);
}