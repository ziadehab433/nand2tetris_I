// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

(START)

@SCREEN
D=A
@R0
M=D
@8192
D=A
@n
M=D

(LOOP)
@n  // if the whole screen is filled then start over
D=M
@START
D;JEQ

@KBD
D=M
@COLORBLACK
D;JNE

@R0
A=M
M=0

@CONTINUE
0;JMP

(COLORBLACK)
@R0
A=M
M=-1

(CONTINUE)
@n
M=M-1

@R0
M=M+1

@LOOP
0;JMP
