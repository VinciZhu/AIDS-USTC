.ORIG x3000
ADD R5, R0, #-3
BRzp BRANCH1
ADD R7, R0, #0
BRnzp BRANCH2
BRANCH1 ADD R2, R6, #1
ADD R3, R6, #1
ADD R7, R6, #2
ADD R4, R0, #-2
LD R5, DATA1
BRANCH3 ADD R1, R2, R2
ADD R2, R3, #0
ADD R3, R7, #0
ADD R7, R7, R1
AND R7, R7, R5
ADD R4, R4, #-1
BRp BRANCH3
BRANCH2 HALT
DATA1 .FILL x3FF
.FILL x3A2
.FILL xF6
.FILL x182
.FILL x112
.END
