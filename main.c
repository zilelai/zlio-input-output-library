#include "zlio.h"


void output_char(char c){
    write(1, &c, 1);
}
void output_string(char *str){
    while(*str){
        output_char(*str);
        str++;
    }
}

int out (const char *format ...){
    va_list args;
    va_start(args, format);
    int count = 0;
    while (*format){
        if (*format == '%'){
            format++;

            if (*format == 'c'){
                char c = (char)va_arg(args, int);
                output_char(c);
                count++;
            }
            else if (*format == 's'){
                char *s = va_arg(args, char *);
                output_string(s);
            }
        }else{
            output_char(*format);
            count++;
        }format++;
    }

    va_end(args);
    return count;
}

//loop and code execute here
int main(){
    out("Hello World");
}
