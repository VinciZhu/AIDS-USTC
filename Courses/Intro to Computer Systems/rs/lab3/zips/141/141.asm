.ORIG x3000
LD R5, DATA1
ADD R2, R2, #1
ADD R3, R3, #1
ADD R4, R4, #2
ADD R0, R0, #-1
BRz BRANCH1
BRANCH3 ADD R0, R0, #-1
BRz BRANCH2
ADD R1, R2, #0
ADD R2, R3, #0
ADD R3, R4, #0
ADD R4, R1, R1
ADD R4, R4, R3
AND R4, R4, R5
BRnzp BRANCH3
BRANCH1 ADD R4, R4, #-1
BRANCH2 ADD R7, R4, #0
HALT
DATA1 .FILL x3FF
.FILL x3A2
.FILL x12
.FILL x1A2
.FILL x36
.END
