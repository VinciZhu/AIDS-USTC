.ORIG x3000
LD R5, DATA1
AND R7, R7, #0
ADD R1, R7, #1
ADD R2, R7, #1
ADD R3, R7, #2
ADD R0, R0, #-2
BRp BRANCH1
BRn BRANCH2
ADD R7, R7, #2
BRnzp BRANCH3
BRANCH2 ADD R7, R7, #1
BRnzp BRANCH3
BRANCH1 AND R6, R6, #0
BRANCH6 ADD R4, R1, #0
ADD R4, R4, R1
ADD R4, R4, R3
ADD R1, R2, #0
ADD R2, R3, #0
ADD R3, R4, #0
BRANCH5 ADD R6, R3, R5
BRnz BRANCH4
ADD R3, R3, R5
BRnzp BRANCH5
BRANCH4 ADD R0, R0, #-1
BRp BRANCH6
ADD R7, R7, R3
BRANCH3 HALT
DATA1 .FILL xFC00
.FILL x3A2
.FILL x12
.FILL x1A2
.FILL x32
.END
