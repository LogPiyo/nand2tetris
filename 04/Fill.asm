// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

(WHITE)
    // res_kbd = 8224
    @8224
    D=A

    (WHITELOOP)
        // set white
        @SCREEN
        A=D+A
        M=0

        // if (res_kbd == 0) goto LOOP
        @LOOP
        D;JEQ

        // res_kbd--
        D=D-1

        // goto WHITELOOP
        @WHITELOOP
        0;JMP

(BLACK)
    // res_kbd = 8224
    @8224
    D=A

    (BLACKLOOP)
        // set black
        @SCREEN
        A=D+A
        M=-1

        // if (res_kbd == 0) goto LOOP
        @LOOP
        D;JEQ
        
        // res_kbd--
        D=D-1

        // goto BLACKLOOP
        @BLACKLOOP
        0;JMP

(LOOP)
    @KBD
    D=M

    // if (kbd == 0) goto WHITE
    @WHITE
    D;JEQ

    // if (kbd != 0) goto BLACK
    @BLACK
    D;JNE

    // goto loop (infinite loop)
    @LOOP
    0;JMP



