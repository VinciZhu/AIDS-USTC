.ORIG x3000
LD R1, DATA1
LD R2, DATA2
LD R3, DATA1
LD R4, DATA3
AND R7, R7, #0
ADD R0, R0, #-1
BRnz BRANCH1
ADD R0, R0, #-1
BRz BRANCH2
BRANCH3 ADD R5, R1, #0
ADD R1, R2, R2
ADD R2, R3, #0
ADD R3, R3, R5
AND R3, R3, R4
ADD R7, R3, #0
ADD R0, R0, #-1
BRp BRANCH3
BRz BRANCH4
BRANCH2 ADD R7, R7, #1
BRANCH1 ADD R7, R7, #1
BRANCH4 HALT
DATA3 .FILL x3FF
DATA2 .FILL x1
DATA1 .FILL x2
.FILL x2D2
.FILL xF6
.FILL x2E6
.FILL x1F2
.END
