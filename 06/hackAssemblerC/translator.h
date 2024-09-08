#ifndef __TRANSLATOR__
#define __TRANSLATOR__

#include "instruction.h"
#include "symTable.h"

typedef struct mapItem { 
    char *str;
    int value;
}mapItem;

char *translate_instruction (Instruction *i, SymTable *t);
char *translate_ainstruction (Instruction *i, SymTable *t);
char *translate_cinstruction (Instruction *i);

char *to_binary (int v, int size);
int get_value (char *s, mapItem *map, int size);

#endif 
