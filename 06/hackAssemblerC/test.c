#include <stdio.h>
#include <stdlib.h>

#include "symTable.h"

int main (void) { 
    char *s = malloc(sizeof(char) * 4);
    s[0] = 'b';
    s[1] = 'r';
    s[2] = 'u';
    s[3] = '\0';

    for (int i = 0; i < 20; i++) { 
        printf("s[i]: %c \n", s[i]);
        s[i] = '1';
    }
}
