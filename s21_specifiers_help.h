#ifndef SPEC_H
#define SPEC_H

int s21_wctomb(char *dest, wchar_t wc);
int wstr_len(wchar_t *str);
void add_width_to_out(char *str_out, char *temp, arg_info s_arg_inf);
bool wstr_to_str(char *str_out, wchar_t *wchstr, arg_info s_arg_inf);
void str_to_str(char *str_out, char *str_arg, arg_info s_arg_inf);
bool wchar_to_str(char *str_out, wchar_t ch, arg_info *s_arg_inf);
bool char_to_str(char *str_out, char ch, arg_info *s_arg_inf);
int int_to_str(arg_int x, char *str, int d);
bool get_u_arg(char *str_out, arg_info s_arg_inf, va_list va_list, char spc);
void process_u_int(char *str_out, arg_u u, arg_info s_arg_inf, char den);
int u_int_to_str(arg_u x, char *str, int d, char den, arg_info s);
void process_int(char *str_out, arg_int s, arg_info s_arg_inf);
int size_out(arg_info s_arg_inf);
bool add_sign(char *str, ld x, arg_info s_arg_inf);
void reverse(char *str, int len);
void lftoa(ld n, char *res, int r_size, int afterpoint, arg_info s_arg_inf);
void process_ldouble(char *str_out, ld arg_ld, arg_info s_arg_inf);
void process_double(char *str_out, double arg_d, arg_info s_arg_inf);
void ftoa(double n, char *res, int r_size, int afterpoint, arg_info s_arg_inf);
bool get_eg_arg(char *str_out, arg_info s_arg_inf, va_list va_list, char e);
int process_e(char *str_out, double arg_d, arg_info s_arg_inf, char e, bool rmtrzrs);
int process_le(char *str_out, ld arg_ld, arg_info s_arg_inf, char e, bool rmtrzrs);
int offset_e(double n);
int offset_le(ld n);
void rtrzrs(char *res, arg_info s_arg);
void add_postfix(char *str_res, int offset, char e);
void process_g(char *str_out, double arg_d, arg_info s_arg_inf, char e);
void add_nan(char *str, arg_info s_arg_inf, ld x);
void add_inf(char *str, arg_info s_arg_inf, ld x);

#endif