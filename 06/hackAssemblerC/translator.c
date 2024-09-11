#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "translator.h"
#include "symTable.h"

static mapItem jump[] = { 
    {"JGT", 1}, {"JEQ", 2}, {"JGE", 3}, {"JLT", 4},
    {"JNE", 5}, {"JLE", 6}, {"JMP", 7}
};

static mapItem comp[] = { 
    {"0",   42},
    {"1",   63},
    {"-1",  58},
    {"D",   12},
    {"A",   48}, {"M",   48},
    {"!D",  13},
    {"!A",  49}, {"!M",  49},
    {"-D",  15},
    {"-A",  51}, {"-M",  51},
    {"D+1", 31},
    {"1+D", 31},
    {"A+1", 55}, {"M+1", 55},
    {"1+A", 55}, {"1+M", 55},
    {"D-1", 14},
    {"A-1", 50}, {"M-1", 50},
    {"D+A",  2}, {"D+M",  2},
    {"A+D",  2}, {"M+D",  2},
    {"D-A", 19}, {"D-M",  19},
    {"A-D",  7}, {"M-D",  7},
    {"D&A",  0}, {"D&M",  0},
    {"A&D",  0}, {"M&D",  0},
    {"D|A", 21}, {"D|M",  21},
    {"A|D", 21}, {"M|D",  21}
};

static mapItem dest[] = { 
    {"M",   1}, {"D",   2}, {"MD",  3}, {"DM",  3}, {"A",   4},
    {"AM",  5}, {"MA",  5}, {"AD",  6}, {"DA",  6}, {"AMD", 7},
    {"ADM", 7}, {"DAM", 7}, {"DMA", 7}, {"MAD", 7}, {"MDA", 7}
};

char *translate_instruction (Instruction *i, SymTable *t) { 
    if (i->type == A) { 
        return translate_ainstruction(i, t);
    } else { 
        return translate_cinstruction(i);
    }
}

char *translate_ainstruction (Instruction *i, SymTable *t) { 
    char *bin;
    if (isalpha(i->value.a_instruction.value[0])) { 
        bin = to_binary(get(t, i->value.a_instruction.value), 16);
    } else { 
        bin = to_binary(atoi(i->value.a_instruction.value), 16);
    }

    char *res = (char *) malloc(sizeof(char) * 2);
    if (res == NULL) { 
        printf("failed to allocate mem in translate_ainstruction func \n");
        exit(1);
    }
    res[0] = 0;

    strcat(res, bin);
    strcat(res, "\0");

    return res;
}

char *translate_cinstruction (Instruction *i) { 
    char *res = malloc(sizeof(char) * 16);
    if (res == NULL) { 
        printf("failed to allocate mem in translate_cinstruction func \n");
        exit(1);
    }
    res[0] = '\0';

    if (strstr(i->value.c_instruction.comp, "M")) { 
        strcat(res, "1111");
        strcat(res, to_binary(get_value(i->value.c_instruction.comp, comp, sizeof(comp)), 6));
    } else { 
        strcat(res, "1110");
        strcat(res, to_binary(get_value(i->value.c_instruction.comp, comp, sizeof(comp)), 6));
    }

    if (i->value.c_instruction.dest[0] != '\0') { 
        strcat(res, to_binary(get_value(i->value.c_instruction.dest, dest, sizeof(dest)), 3));
    } else { 
        strcat(res, to_binary(0, 3));
    }

    if (i->value.c_instruction.jmp[0] != '\0') { 
        strcat(res, to_binary(get_value(i->value.c_instruction.jmp, jump, sizeof(jump)), 3));
    } else { 
        strcat(res, to_binary(0, 3));
    }

    return res;
}

char *to_binary (int v, int size) { 
    char *res = (char *) malloc(sizeof(char) * (size));
    if (res == NULL) { 
        printf("failed to allocate in function: to_binary \n");
        exit(1);
    }

    int r;
    for (int i = (size - 1); i >= 0; i--) { 
        if (v == 0) { 
            res[i] = '0';
            continue;
        }

        r = v % 2;
        v = v / 2;

        res[i] = r + '0';
    }

    return res;
}

int get_value (char *s, mapItem *map, int size) { 
    if (s[0] == '\0') {
        return 0;
    }

    for (int i = 0; i < size; i++) { 
        if (strcmp(map[i].str, s) == 0) { 
            return map[i].value;
        }
    }

    return 0;
}
