#include "sprintf.h"

int main() {
    // char str[100];
    // sprintf(str, "a dsa asda %e", 1.72);
    arg_info flags = {1};
    flags.system_of_computation = 10;
    char str0[20] = {"\0"};
    char str1[20] = {"\0"}; 
    flags.l = 1;
    flags.minus = 1;
    flags.width = 10;
    specifier_d_or_i(str0, flags);
    sprintf(str1, "%+-10ld", (long int)145);
    // str0[10] = '\0';s
    printf("my_sprtf: '%s'\n", str0);
    printf("st_sprtf: '%s'\n", str1);
    return 0;
}




//Start
void specifier_d_or_i(char *str, arg_info flags) {
    long int num = 145;
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
            str[i++] = ' ';
        }
    }
    if(new_str) free(new_str);
    // return str;
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
//END


//START
char specifier_c(char *str, arg_info flags, va_list *arguments) {
    if(flags.l){
        wchar_t w_c;
        w_c = va_arg(*arguments, wchar_t);  
        form_wchar(str, w_c, flags);
    } else {
        char ch;
        ch = va_arg(*arguments, int);
        form_char(str, ch, flags);
    }
}
//flag l in s
void form_wchar(char *str, wchar_t w_c, arg_info flags) {
    if(!flags.minus && flags.width) {
        char tmp[BUFF_SIZE] = {'\0'};
        wcstombs(tmp, &w_c, BUFF_SIZE);
        for(s21_size_t i = 0; i < flags.width - strlen(tmp); i++)
            str[i] = ' ';
        strcat(str, tmp);
    } else if(flags.width) {
        wcstombs(str, &w_c, BUFF_SIZE);
        for(int i = strlen(str); i < flags.width; i++)
            str[i] = ' ';
    } else 
        wcstombs(str, &w_c, BUFF_SIZE);
}

//standart size
void form_char(char *str, char ch, arg_info flags) {
    if(!flags.minus && flags.width) {
        for(int i = 0; i < flags.width;i++) {
            str[i] = ' ';
            if(i == flags.width - 1)
                str[i] = ch;
        }
    } else if(flags.width) {
        str[0] = ch;
        for(int i = 1; i < flags.width;i++)
            str[i] = ' ';
    } else
        str[0] = ch;
}
//END



//START flag s 
char specifier_s(char *str, arg_info flags) {
    if(flags.l) {
        wchar_t *wchar_str = (wchar_t *)"str_wchar";
        printf("%ls\n", wchar_str);
        // wchar_str = va_arg(*arguments, wchar_t *);
        form_wchar_str(str, wchar_str, flags);
    } else {
        char *va_str = "str_char";
        // va_str = va_arg(*arguments, char *);
        form_char_str(str, va_str, flags);
    }
}

// flag l in s 
void form_wchar_str(char *str,wchar_t *wchar_str, arg_info flags) {
    char tmp[BUFF_SIZE] = {'\0'};
    char str_wcstombs[BUFF_SIZE] = {'\0'};
    wcstombs(str_wcstombs, wchar_str, BUFF_SIZE);
    strcpy(tmp, str_wcstombs);

    if(flags.precision)
        tmp[flags.precision] = '\0';
    
    int shift = flags.width - strlen(tmp);
    int tmp_len = strlen(tmp);

    if(flags.minus && shift > 0) {
        strcpy(str, tmp);
        memset(str + tmp_len, ' ', shift);
    } else if(shift > 0) {
        memset(str, ' ', shift);
        strcpy(str + shift, tmp);
    } else {
        strcpy(str, tmp);
    }
}

void form_char_str(char *str, char *va_str, arg_info flags) {
    char tmp[BUFF_SIZE] = {'\0'};
    strcpy(tmp , va_str);
    
    if(flags.precision) 
        tmp[flags.precision] = '\0';

    int shift = flags.width - strlen(tmp);
    int tmp_len = strlen(tmp);

    if(flags.minus && shift > 0) {
        strcpy(str, tmp);
        memset(str + tmp_len, ' ', shift);
    } else if(shift > 0){
        memset(str, ' ', shift);
        strcpy(str + shift, tmp);
    } else
        strcpy(str, tmp);
}
//END