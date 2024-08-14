// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

@R0
D=M
@R1
D=D-M

@FIRST
D;JGE

@R1
D=M
@n
M=D
@R0
D=M
@R2
M=D
@inc
M=D

@CONTINUE
0;JMP

(FIRST)
@R0
D=M
@n
M=D
@R1
D=M
@R2
M=D
@inc
M=D

(CONTINUE)
@n
D=M-1
@END
D;JEQ

@inc
D=M
@R2
M=D+M

@n
M=M-1
@CONTINUE
0;JMP

(END)
@END
0;JMP
