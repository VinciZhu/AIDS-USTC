.ORIG x3000
ADD R7, R1, #1
ADD R0, R0, #-1
BRnz BRANCH1
ADD R7, R7, #1
ADD R0, R0, #-1
BRz BRANCH1
ADD R1, R1, #1
ADD R2, R2, #1
LD R4, DATA1
BRANCH2 ADD R3, R1, R1
ADD R1, R2, #0
ADD R2, R7, #0
ADD R7, R7, R3
AND R7, R7, R4
ADD R0, R0, #-1
BRp BRANCH2
BRANCH1 HALT
DATA1 .FILL x3FF
.FILL x3A2
.FILL xF6
.FILL x2E6
.FILL x1
.END
