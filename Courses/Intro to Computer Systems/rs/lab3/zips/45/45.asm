.ORIG x3000
ADD R0, R0, #-1
BRp BRANCH1
ADD R4, R4, #1
BRnzp BRANCH2
BRANCH1 ADD R0, R0, #-1
BRp BRANCH3
ADD R4, R4, #2
BRnzp BRANCH2
BRANCH3 ADD R1, R1, #1
ADD R2, R2, #1
ADD R3, R3, #2
LD R6, DATA1
BRANCH6 ADD R4, R1, R1
ADD R4, R4, R3
BRANCH5 ADD R5, R4, R6
BRn BRANCH4
ADD R4, R5, #0
BRnzp BRANCH5
BRANCH4 ADD R1, R2, #0
ADD R2, R3, #0
ADD R3, R4, #0
ADD R0, R0, #-1
BRp BRANCH6
BRANCH2 ADD R7, R4, #0
HALT
DATA1 .FILL xFC00
.FILL x3A2
.FILL x4
.FILL xA
.FILL x292
.END
