.ORIG x3000
ADD R1, R1, #1
ADD R2, R2, #1
ADD R3, R3, #2
ADD R5, R5, #1
ADD R6, R6, #10
BRANCH1 ADD R5, R5, R5
ADD R6, R6, #-1
BRp BRANCH1
ADD R5, R5, #-1
ADD R0, R0, #-2
BRz BRANCH2
BRn BRANCH3
BRANCH5 ADD R0, R0, #-1
BRn BRANCH4
ADD R4, R2, #0
ADD R2, R3, #0
ADD R1, R1, R1
ADD R3, R3, R1
AND R3, R5, R3
ADD R1, R4, #0
ADD R7, R3, #0
BRnzp BRANCH5
BRANCH2 ADD R7, R7, #1
BRANCH3 ADD R7, R7, #1
BRANCH4 HALT
.FILL x3A2
.FILL x106
.FILL x2D2
.FILL x2E6
.END
