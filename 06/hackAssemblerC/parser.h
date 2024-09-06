#ifndef __PARSER__
#define __PARSER__

#include "instruction.h"

typedef struct Parser { 
    char *file_name;
}Parser;

void parse_file (Parser *parser);
Instruction *parse_instruction (char i[]);
Instruction *parse_ainstruction (char i[]);
Instruction *parse_cinstruction (char i[]);

char *trim (char *s);
char *split(char *s, char d);

#endif
