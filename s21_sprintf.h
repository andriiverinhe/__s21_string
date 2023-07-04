#ifndef S21_SPRINTH
#define S21_SPRINTH

#include <stdbool.h>

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

#endif