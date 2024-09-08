#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "parser.h"
#include "instruction.h"
#include "translator.h"
#include "symTable.h"

void parse_file (Parser *parser) {
    FILE *file = fopen(parser->file_name, "r");
    if (file == NULL) { 
        perror("Failed to open file.");
        exit(1);
    }

    char *output_file_name = strcat(strtok(parser->file_name, "."), ".hack");
    FILE *output_file = fopen(output_file_name, "w");
    if (output_file == NULL) { 
        perror("Failed to create a hack file.");
        exit(1);
    }

    SymTable *t = new_symTable();

    first_pass(file, t);
    fseek(file, 0, SEEK_SET);
    second_pass(file, t, output_file);

    fclose(file);
    fclose(output_file);
}

void first_pass (FILE *file, SymTable *t) { 
    size_t len = 40;
    char *line = NULL;
    char instr[200];
    int line_no = 0;
    while (getline(&line, &len, file) != -1) { 
        strcpy(instr, trim(line));

        if (instr[0] == '/') continue;

        if (instr[0] == '(') { 
            char *label = split(&instr[1], ')');
            if (get(t, label) == -1) { 
                add_entry(t, label, line_no);
            }

            continue;
        }

        line_no++;
    }
}

void second_pass (FILE *file, SymTable *t, FILE *output_file) { 
    size_t len = 40;
    char *line = NULL;
    char instr[200];
    while (getline(&line, &len, file) != -1) { 
        strcpy(instr, trim(line));

        if (instr[0] == '/' || instr[0] == '(') {  // ignore comments
            continue;
        }

        if ((instr[0] == '@' && !isdigit(instr[1]))) { 
            char *var = split(&instr[1], '\0');
            if (get(t, var) == -1) { 
                add_entry(t, var, -1);
            }
        }

        Instruction *instruction = parse_instruction(instr);
        char *bin = translate_instruction(instruction, t);

        int res = fputs(bin, output_file);
        if (res == EOF) { 
            perror("Error while writing to the output file.");
            exit(1);
        }
        
        fputs("\n", output_file);
    }
}

char *trim (char *s) { 
    while (*s == ' ') s++;

    if (*s == '\n') return "/"; // so i can check for empty lines

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

    Instruction *inst_ptr = (Instruction *) malloc(sizeof(Instruction));
    if (inst_ptr == NULL) { 
        perror("malloc failed");
        exit(1);
    }

    inst_ptr->type = A;
    strcpy(inst_ptr->value.a_instruction.value, v);

    return inst_ptr;
}

Instruction *parse_cinstruction(char in[]) { 
    Instruction *inst_ptr = (Instruction *) malloc(sizeof(Instruction));
    if (inst_ptr == NULL) { 
        perror("malloc failed");
        exit(1);
    }

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
