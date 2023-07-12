#ifndef SPEC_H
#define SPEC_H

int s21_wctomb(char *dest, wchar_t wc);
int wstr_len(wchar_t *str);
void adjust_width_str(char *str_out, char *temp, arg_info s_arg_inf);
bool wstr_to_str(char *str_out, wchar_t *wchstr, arg_info s_arg_inf);
void str_to_str(char *str_out, char *str_arg, arg_info s_arg_inf);
bool wchar_to_str(char *str_out, wchar_t ch, arg_info s_arg_info);
void char_to_str(char *str_out, char ch, arg_info s_arg_info);

#endif