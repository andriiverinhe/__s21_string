#include "s21_sprintf.h"

bool specifier_s(char *str_out, arg_info s_arg_inf, va_list va_list)
{
  if (s_arg_inf.l)
  {
    wchar_t *wchar_str = va_arg(va_list, wchar_t *);
    if (wstr_to_str(str_out, wchar_str, s_arg_inf))
      return true;
  }
  else
  {
    char *str_arg = va_arg(va_list, char *);
    str_to_str(str_out, str_arg, s_arg_inf);
  }
  return false;
}

bool specifier_c(char *str_out, arg_info s_arg_inf, va_list va_list)
{
  if (s_arg_inf.l)
  {
    wchar_t one_char = va_arg(va_list, wchar_t);
    if (wchar_to_str(str_out, one_char, s_arg_inf))
      return true;
  }
  else
  {
    char one_char = va_arg(va_list, int);
    char_to_str(str_out, one_char, s_arg_inf);
  }
  return false;
}

int s21_wctomb(char *dest, wchar_t wc)
{
  if (wc < 0x80)
  {
    *dest = (char)wc;
    return 1;
  }
  return 0;
}

int wstr_len(wchar_t *str)
{
  int len = 0;
  while (*str++ != '\0')
    len++;
  return len;
}

void adjust_width_str(char *str_out, char *temp, arg_info s_arg_inf)
{
  if (s_arg_inf.width)
  {
    int shift = *s_arg_inf.width - strlen(temp);

    if (s_arg_inf.minus && shift > 0)
    {
      strcat(str_out, temp);
      int out_len = strlen(str_out);
      memset(str_out + out_len, ' ', shift);
    }
    else if (shift > 0)
    {
      int out_len = strlen(str_out);
      memset(str_out + out_len, ' ', shift);
      strcat(str_out, temp);
    }
    else
    {
      strcat(str_out, temp);
    }
  }
  else
    strcat(str_out, temp);
}

bool wstr_to_str(char *str_out, wchar_t *wchstr, arg_info s_arg_inf)
{
  int error = false;
  if (s_arg_inf.precision)
    wchstr[*s_arg_inf.precision] = '\0';
  int w_str_s = wstr_len(wchstr);
  if (w_str_s) {
    char *temp = malloc(w_str_s * 4);
    int ind = 0;
    while (*wchstr != '\0')
    {
      ind += s21_wctomb(temp + ind, *wchstr++);
      if (!ind)
        break;
    }
    if (!ind)
      error = true;
    adjust_width_str(str_out, temp, s_arg_inf);
    free(temp);
  }
  return error;
}

void str_to_str(char *str_out, char *str_arg, arg_info s_arg_inf)
{
  int str_arg_len = strlen(str_arg);
  if (s_arg_inf.precision && *s_arg_inf.precision < str_arg_len)
    str_arg[*s_arg_inf.precision] = '\0';
  if (str_arg_len) {
    char *temp = malloc(str_arg_len);
    int i = -1;
    while (str_arg[++i] != '\0')
      temp[i] = str_arg[i];
    adjust_width_str(str_out, temp, s_arg_inf);
    free(temp);
  }
}

bool wchar_to_str(char *str_out, wchar_t ch, arg_info s_arg_info)
{
  bool error = false;
  char *temp = malloc(2);
  if (!s21_wctomb(temp, ch))
    error = true;
  adjust_width_str(str_out, temp, s_arg_info);
  free(temp);
  return error;
}

void char_to_str(char *str_out, char ch, arg_info s_arg_info)
{
  char *temp = malloc(2);
  temp[0] = ch;
  adjust_width_str(str_out, temp, s_arg_info);
  free(temp);
}

// int main()
// {
//   char testing[100] = "";

//   char *new = specifier_s(testing, give_flag_struct());
//   printf("%s", new);
//   return 0;
// }