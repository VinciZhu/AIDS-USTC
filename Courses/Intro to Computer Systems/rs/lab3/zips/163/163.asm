.ORIG x3000
ADD R3, R3, #1
ADD R0, R0, #-1
BRn BRANCH1
ADD R1, R3, #0
ADD R0, R0, #-1
BRn BRANCH1
ADD R2, R3, #0
ADD R3, R3, #1
ADD R0, R0, #-1
BRn BRANCH1
BRANCH3 ADD R4, R1, R1
ADD R4, R4, R3
LD R5, DATA1
LD R6, DATA2
ADD R4, R4, R6
BRANCH2 ADD R4, R4, R5
BRn BRANCH2
ADD R1, R2, #0
ADD R2, R3, #0
ADD R3, R4, #0
ADD R0, R0, #-1
BRzp BRANCH3
BRANCH1 ADD R7, R3, #0
HALT
DATA1 .FILL x400
DATA2 .FILL xF400
.FILL x3A2
.FILL x3F6
.FILL x2E6
.FILL x172
.END
