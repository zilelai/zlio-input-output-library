#ifndef ZLIO_H
#define ZLIO_H

#include <stdarg.h>
#include <unistd.h>
#include <stdbool.h> 

#ifdef __cplusplus
extern "C" {
#endif

int out(const char *format, ...);

typedef enum {
    INPUTINT,
    INPUTDOUBLE,
    INPUTBOOL,
    INPUTSTR
} InputType;

typedef struct {
    InputType type;
    union {
        int intvalue;
        double doublevalue;
        bool boolvalue;
        char stringvalue[256];
    } data;
} InputValue;

InputValue in(const char *prompt);

#ifdef __cplusplus
}
#endif

#endif
