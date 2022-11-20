;1234 ADD R1, R2, #5
;abcd AND R1, R2, #1
;一二三四 NOT R1, R2
.ORIG x3000
;
;
BinarytoASCII   ST R0, BtoA_Save0
                ST R1, BtoA_Save1
                ST R2, BtoA_Save2
                ST R3, BtoA_Save3       ;ADD R1, R2, #5
                LD R1, BtoA_ASCIIBUFF
                ADD R0,R0,#0
                BRn NegSign
                LD R2, ASCIIplus
                STR R2,R1,#0
                BRnzp Begin100
NegSign         LD R2, ASCIIminus
                STR R2,R1,#0
                NOT R0,R0
                ADD R0,R0,#1
;
Begin100        LD R2, ASCIIoffset
;
                LD R3,Neg100
Loop100         ADD R0, R0, R3
                BRn End100
                ADD R2,R2,#1
                BRnzp Loop100
;
End100          STR R2,R1,#1
                LD R3,Pos100
                ADD R0,R0,R3
;
                LD R2,ASCIIoffset
;
Loop10          ADD R0, R0, #-10
                BRn End10
                ADD R2,R2,#1
                BRnzp Loop10
;
End10           STR R2, R1, #2
                ADD R0, R0, #10
Begin1          LD R2, ASCIIoffset ;prepare
                ADD R2, R2, R0
                STR R2, R1, #3
                LD R0, BtoA_Save0
                LD R1, BtoA_Save1
                LD R2, BtoA_Save2
                LD R3, BtoA_Save3
                LD R0, BtoA_ASCIIBUFF
                ldR R1, R0, #0
                LDR R2, R0, #1
                LDR R3, R0, #2
                LDR R4, R0, #3
                HALT
;
ASCIIplus       .FILL x002B
ASCIIminus      .FILL x002D
ASCIIoffset     .FILL x0030
Neg100          .FILL #-100
Pos100          .FILL #100
BtoA_Save0      .BLKW #1
BtoA_Save1      .BLKW #1
BtoA_Save2      .BLKW #1
BtoA_Save3      .BLKW #1
BtoA_ASCIIBUFF  .FILL x4000
Prom            .STRINGZ "this is a program!"
.END