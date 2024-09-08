#ifndef __PARSER__
#define __PARSER__

#include <stdio.h>

#include "instruction.h"
#include "symTable.h"

typedef struct Parser { 
    char *file_name;
}Parser;

void parse_file (Parser *parser);
void first_pass (FILE *file, SymTable *t);
void second_pass (FILE *file, SymTable *t, FILE *output_file);

Instruction *parse_instruction (char i[]);
Instruction *parse_ainstruction (char i[]);
Instruction *parse_cinstruction (char i[]);

char *trim (char *s);
char *split(char *s, char d);

#endif
