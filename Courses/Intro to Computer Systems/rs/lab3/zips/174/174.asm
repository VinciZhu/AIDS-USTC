.ORIG x3000
ADD R1, R1, #1
ADD R2, R2, #2
ADD R3, R3, #4
LD R4, DATA1
ADD R0, R0, #-1
BRz BRANCH1
ADD R0, R0, #-1
BRz BRANCH2
ADD R0, R0, #-1
BRz BRANCH3
BRp BRANCH4
BRANCH1 ADD R7, R1, #0
BRnzp BRANCH5
BRANCH2 ADD R7, R2, #0
BRnzp BRANCH5
BRANCH3 ADD R7, R3, #0
BRnzp BRANCH5
BRANCH4 ADD R7, R1, #0
ADD R7, R7, R1
ADD R7, R7, R3
AND R7, R7, R4
ADD R1, R2, #0
ADD R2, R3, #0
ADD R3, R7, #0
ADD R0, R0, #-1
BRp BRANCH4
BRANCH5 HALT
DATA1 .FILL x3FF
.FILL x3A2
.FILL xF6
.FILL x2E6
.FILL x92
.END
