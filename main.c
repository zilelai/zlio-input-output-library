#include "zlio.h"
#include "zlio.c"

int main(){
    out("This is the out command in zlio.h library\n");
    InputValue input = in("Type something... ");
    if (input.type == INPUTINT){
        out("Integer");
    }
    else if (input.type == INPUTBOOL){
        out("Bool/Boolean");
    }
    else if (input.type == INPUTDOUBLE){
        out("Float/Double");
    }
    else if (input.type == INPUTSTR){
        out("Character/String");
    }
}
