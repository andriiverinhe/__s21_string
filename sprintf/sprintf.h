#ifndef SPRINTF
#define SPRINTF

#include "../s21_string.h"
#include <stdbool.h>
#include <stdarg.h>

#define BUFF_SIZE 1024

typedef struct 
{
  // flags
  bool plus;   //Заставляет явно указывать знак плюс или минус 
  bool minus;  //Выравнивание по левому краю
  bool space;  //Если знак не будет выведен, перед значением вставляется пробел. +символ под знак
  bool zeros;  //Заполняет число слева нулями
  bool hash;   //со спецификаторами o, x или X перед числом вставляется 0, 0x или 0X 
  // width
  int width;
  // precision
  int precision;
  bool dot;
  // length
  bool h; // Аргумент интерпретируется как короткое int или короткое int без знака (применяется только к целочисленным спецификаторам: i, d, o, u, x и X)
  bool l; // Аргумент интерпретируется как длинное int или длинное int без знака для целочисленных спецификаторов (i, d, o, u, x и X) и как широкий символ или строка широких символов для спецификаторов c и s.
  bool L; // Аргумент интерпретируется как длинный double (применяется только к спецификаторам с плавающей точкой − e, E, f, g и G).

  int system_of_computation;
  bool flag_to_size;  

} arg_info;

// specifier d and i
s21_size_t get_size_for_decimal(arg_info *flags, long int num);
int decimal_to_string(arg_info flags, long int num, char *new_str, s21_size_t size_arr);
void specifier_d_or_i(char *str, arg_info flags);


//specifier c
char specifier_c(char *str, arg_info flags, va_list *arguments);
void form_wchar(char *str, wchar_t w_c, arg_info flags);
void form_char(char *str, char ch, arg_info flags);
//

//specifier s
  char specifier_s(char *str, arg_info flags);
  void form_wchar_str(char *str,wchar_t *wchar_str, arg_info flags);
  void form_char_str(char *str, char *va_str, arg_info flags);
//
#endif