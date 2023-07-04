#include "sprintf.h"
char *specifier_d_or_i(char *str, arg_info flags);
int main() {
    // char str[100];
    // sprintf(str, "a dsa asda %e", 1.72);
    arg_info flags = {1};
    flags.system_of_computation = 10;
    // get_size_for_decimal(&flags, 1233);
    char str[15];
    specifier_d_or_i(str, flags);
    // printf("%s\n",str);
    printf("Str: %s\n", str);
    return 0;
}

int s21_sprintf(char *str, const char *format, ...) { 
    
    va_list argument;
    va_start(argument, format);


    va_end(argument);

}

char *specifier_d_or_i(char *str, arg_info flags) {
    long int num = 148;
    // if(flags.l)
    //     num = (long int)va_arg(*arguments, long int);
    // else if(flags.h)
    //     num = (int)va_arg(*arguments, int);
    // else
    //     num = (int)va_arg(*arguments, int);
        
    s21_size_t size_arr = get_size_for_decimal(&flags, num);
    
    char *new_str = malloc(sizeof(char) * size_arr);
    if(new_str) {
        int i = decimal_to_string(flags, num, new_str, size_arr);
        for(int j = i - 1, k = 0; j >= 0; j--, k++){
            str[k] = new_str[j];
        }
        str[i] = '\0';
        while(i < flags.width){
            *str = ' ';
            str++;
        }
    }
    if(new_str) free(new_str);
    return str;
}






s21_size_t get_size_for_decimal(arg_info *flags, long int num) {
    s21_size_t result = 0;
    long int tmp_num = num;
    tmp_num < 0 ? (tmp_num = -tmp_num) : (tmp_num = tmp_num);

    while (tmp_num != 0) {
        tmp_num /= 10;
        result++;
    }
    if(tmp_num == 0 && result == 0 && (flags->width || flags->space || (flags->precision)))
        result++;

    if((s21_size_t)flags->width > result)
        result = flags->width;

    if((s21_size_t)flags->precision > result)
        result = flags->precision;

    if(flags->space || flags->plus || num < 0){
        flags->flag_to_size = 1;
        result++;
    }

    if(result == 0 && tmp_num == 0 && !flags->space && !flags->dot && !flags->plus && !flags->width)
        result++;
    // printf("%ld\n", result);
    return result;
}

int decimal_to_string(arg_info flags ,long int num, char *new_str, s21_size_t size_arr) {
    int flag = 0;
    if(num < 0){
        flag = 1;
        num = -num;
    } 
    int i = 0;
    long int tmp_num = num;
//if num == 0
    if((tmp_num == 0 && (flags.precision || flags.space || flags.width)) || 
        (tmp_num == 0 && !flags.precision && !flags.space && !flags.width && !flags.dot)) {
            char ch = tmp_num % flags.system_of_computation + '0';
            new_str[i] = ch;
            i++;
            size_arr--;
            tmp_num /= 10;
        }
//if num != 0
    while (tmp_num && new_str && size_arr) {
        char ch = (tmp_num % flags.system_of_computation) + '0';
        new_str[i++] = ch;
        size_arr--;
        tmp_num /= 10;
    }
    
    if(flag) num = -num;

    if(flags.precision - i > 0) {
        flags.precision -= i;
        flags.zeros = 1;
    } else 
        flag = 1;
    //not memory for zero
    if(size_arr == 1 && flags.zeros && flags.flag_to_size)
        flags.zeros = 0;

    //flag zeros
    while (flags.zeros && new_str && (size_arr - flags.flag_to_size > 0) && (flags.precision || flag)) 
    {
        if((size_arr == 1 && flags.flag_to_size == 1))
            break;
        new_str[i++] = '0';
        size_arr--;
        flags.precision--;
    }
    //flag +/-/space
    if(flags.space && num >= 0 && size_arr) {
        new_str[i++] = ' ';
        size_arr--;
    }
    if(num < 0 && size_arr) { 
        new_str[i++] = '-';
        size_arr--;    
    }
    if(num > 0 && flags.plus && size_arr) { 
        new_str[i++] = '+';
        size_arr--;    
    }
    //если осталось место
    if(size_arr > 0 && flags.minus == 0) { 
        while ((size_arr - flags.flag_to_size > 0) && new_str) 
        {
            new_str[i++] = ' ';
            size_arr--;
        }
    }
    return i;
}