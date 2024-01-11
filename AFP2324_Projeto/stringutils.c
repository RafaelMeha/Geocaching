#include "stringutils.h"
#include <string.h>

void rtrim(char *str) {
    char discard[] = "\t\n\v\f\r ";

    int i = strlen(str) - 1;
    while (i >= 0 && strchr(discard, str[i]) != NULL) {
        str[i] = '\0';
        i--;
    }
}

void replace(char *str, char what, char replace) {
    int len = strlen(str);
    for(int i=0; i < len; i++) {
        if( str[i] == what ) {
            str[i] = replace;
        }
    }
}