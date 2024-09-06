#ifndef __INSTRUCTION__
#define __INSTRUCTION__

typedef struct Ainstruction { 
    int value;
}Ainstruction;

typedef struct Cinstruction { 
    char dest[4];
    char comp[4];
    char jmp[4];
}Cinstruction;

typedef enum InstructionType { 
    A,
    C
}InstructionType;

typedef union { 
    Ainstruction a_instruction;
    Cinstruction c_instruction;
}InstructionValue;

typedef struct Instruction { 
    InstructionType type;
    InstructionValue value;
}Instruction;


#endif
