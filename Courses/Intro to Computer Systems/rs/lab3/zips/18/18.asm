.ORIG x3000
ADD R4, R4, #1
ADD R5, R5, #1
ADD R6, R6, #2
ADD R1, R1, #2
BRANCH1 ADD R1, R1, #1
ADD R2, R4, R4
ADD R7, R2, R6
ADD R4, R5, #0
ADD R5, R6, #0
LD R2, DATA1
AND R7, R7, R2
ADD R6, R7, #0
NOT R2, R1
ADD R2, R2, #1
ADD R3, R2, R0
BRp BRANCH1
ADD R2, R0, #-2
BRp BRANCH2
LD R7, DATA2
ADD R2, R2, #0
BRz BRANCH3
BRn BRANCH2
BRANCH3 ADD R7, R7, #1
BRANCH2 HALT
DATA2 .FILL x1
DATA1 .FILL x3FF
.FILL x3A2
.FILL xF6
.FILL x182
.FILL x3B2
.END
