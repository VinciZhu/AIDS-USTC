.ORIG x3000
AND R1, R1, #0
ADD R1, R1, #1
ADD R2, R1, #0
ADD R7, R1, #0
ADD R0, R0, #-1
BRnz BRANCH1
ADD R7, R7, #1
BRANCH2 ADD R0, R0, #-1
BRz BRANCH1
ADD R3, R2, R2
ADD R2, R1, #0
ADD R1, R7, #0
ADD R7, R1, R3
BRnzp BRANCH2
BRANCH1 LD R4, DATA1
LD R5, DATA2
ADD R7, R7, R4
BRzp BRANCH1
ADD R7, R7, R5
TRAP x19
DATA1 TRAP x0
DATA2 BRz BRANCH3
BRANCH3 BRp BRANCH4
BR BRANCH5
BR BRANCH6
BRANCH5 BR BRANCH7
.END
