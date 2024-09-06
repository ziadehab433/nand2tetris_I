#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "parser.h"
#include "instruction.h"
#include "translator.h"

void parse_file (Parser *parser) {
    FILE *file = fopen(parser->file_name, "r");
    if (file == NULL) { 
        perror("Failed to open file.");
        exit(1);
    }

    char *output_file_name = strcat(strtok(parser->file_name, "."), ".hack");
    FILE *output_file = fopen(output_file_name, "w");
    printf("output file name: %s \n", output_file_name);
    if (output_file == NULL) { 
        perror("Failed to create a hack file.");
        exit(1);
    }

    size_t len = 40;
    char *instr = NULL;
    while (getline(&instr, &len, file) != -1) { 
        strcpy(instr, trim(instr));

        if (instr[0] == '/') {  // ignore comments
            continue;
        }

        Instruction *instruction = parse_instruction(instr);
        char *bin = translate_instruction(instruction);

        int res = fputs(bin, output_file);
        if (res == EOF) { 
            perror("Error while writing to the output file.");
            exit(1);
        }
        
        fputs("\n", output_file);
    }

    fclose(output_file);
}

char *trim (char *s) { 
    while (*s == ' ') s++;

    if (*s == '\n') return "/";

    char *b = s + strlen(s);
    while (isspace(*--b));
    *(b+1) = '\0';

    return s;
}

Instruction *parse_instruction (char i[]) { 
    if (i[0] == '@') { 
        return parse_ainstruction(i);
    } else { 
        return parse_cinstruction(i);
    }
}

Instruction *parse_ainstruction(char i[]) {
    char v[50];
    int x;
    for (x = 1; i[x] != '\0'; x++) { 
        v[x - 1] = i[x];
    }
    v[x - 1] = '\0';

    int value = atoi(v);

    Instruction *inst_ptr = (Instruction *) malloc(sizeof(Instruction));
    if (inst_ptr == NULL) { 
        perror("malloc failed");
        exit(1);
    }

    inst_ptr->type = A;
    inst_ptr->value.a_instruction.value = value;

    return inst_ptr;
}

Instruction *parse_cinstruction(char in[]) { 
    Instruction *inst_ptr = (Instruction *) malloc(sizeof(Instruction));
    inst_ptr->type = C;

    char *cpos = strchr(in, '=');
    char *jpos = strchr(in, ';');

    if (cpos) { 
        strcpy(inst_ptr->value.c_instruction.dest, split(in, '='));

        if (jpos) { 
            strcpy(inst_ptr->value.c_instruction.comp, split(cpos + 1, ';'));
            strcpy(inst_ptr->value.c_instruction.jmp, split(cpos + 1, '\0'));
        } else { 
            strcpy(inst_ptr->value.c_instruction.comp, split(cpos + 1, '\0'));
        }
    } else if (jpos) { 
        strcpy(inst_ptr->value.c_instruction.comp, split(in, ';'));
        strcpy(inst_ptr->value.c_instruction.jmp, split(jpos + 1, '\0'));
    } else { 
        strcpy(inst_ptr->value.c_instruction.comp, in);
    }

    return inst_ptr;
}

char *split (char *s, char d) { 
    char *p = malloc(sizeof(char) * 4);

    for (int i = 0; i < 20; i++) { 
        if (s[i] == d) { 
            p[i] = '\0';
            break;
        }

        p[i] = s[i];
    }

    return p;
}
