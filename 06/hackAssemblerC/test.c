#include <stdio.h>

#include "symTable.h"

int main (void) { 
    SymTable *t = new_symTable();

    add_entry(t, "hi", 10);
    add_entry(t, "ih", 11);

    printf("hi: %d \n", get_value(t, "hi"));
    printf("ih: %d \n", get_value(t, "ih"));
}
