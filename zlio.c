#include "zlio.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>


void charoutput(char c){
    write(1, &c, 1);
}

void stroutput(const char *str){
    while(*str){
        charoutput(*str);
        str++;
    }
}


int out(const char *format, ...){
    va_list args;
    va_start(args, format);
    int count = 0;

    while (*format){
        if (*format == '%'){
            format++;

            if (*format == 'c'){
                char c = (char)va_arg(args, int);
                charoutput(c);
                count++;
            }
            else if (*format == 's'){
                char *s = va_arg(args, char *);
                if (s) {
                    stroutput(s);
                }
            }
        } else {
            charoutput(*format);
            count++;
        }
        format++;
    }

    va_end(args);
    return count;
}

static void strw(const char *str) {
    if (str) {
        write(STDOUT_FILENO, str, strlen(str));
    }
}

static size_t rlen(char *buf, size_t max_len) {
    size_t i = 0;
    char c;
    while (i < max_len - 1) {
        ssize_t bytes = read(STDIN_FILENO, &c, 1);
        if (bytes <= 0 || c == '\n') break; 
        buf[i++] = c;
    }
    buf[i] = '\0';
    return i;
}

InputValue in(const char *prompt) {
    InputValue result;
    char buffer[256];

    strw(prompt);

    rlen(buffer, sizeof(buffer));

    if (buffer[0] == '\0') {
        result.type = INPUTSTR;
        result.data.stringvalue[0] = '\0';
        return result;
    }

    char *endptr;

    long vall = strtol(buffer, &endptr, 10);
    if (*endptr == '\0') {
        result.type = INPUTINT;
        result.data.intvalue = (int)vall;
        return result;
    }

    double vald = strtod(buffer, &endptr);
    if (*endptr == '\0') {
        result.type = INPUTDOUBLE;
        result.data.doublevalue = vald;
        return result;
    }

    if (strcasecmp(buffer, "true") == 0 || strcmp(buffer, "1") == 0 || strcasecmp(buffer, "yes") == 0) {
        result.type = INPUTBOOL;
        result.data.boolvalue = true;
        return result;
    }
    if (strcasecmp(buffer, "false") == 0 || strcmp(buffer, "0") == 0 || strcasecmp(buffer, "no") == 0) {
        result.type = INPUTBOOL;
        result.data.boolvalue = false;
        return result;
    }

    result.type = INPUTSTR;
    strncpy(result.data.stringvalue, buffer, sizeof(result.data.stringvalue) - 1);
    result.data.stringvalue[sizeof(result.data.stringvalue) - 1] = '\0';

    return result;
}
