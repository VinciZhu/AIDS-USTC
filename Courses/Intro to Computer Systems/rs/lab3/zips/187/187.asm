.ORIG x3000
AND R4, R4, #0
AND R5, R5, #0
AND R7, R7, #0
LD R1, DATA1
LD R2, DATA2
LD R3, DATA3
LD R6, DATA4
ADD R0, R0, #-2
BRnz BRANCH1
BRANCH5 ADD R4, R3, R1
ADD R4, R4, R1
BRANCH3 ADD R5, R4, R6
BRn BRANCH2
ADD R4, R4, R6
BRp BRANCH3
BRANCH2 ADD R1, R2, #0
ADD R2, R3, #0
ADD R3, R4, #0
AND R4, R4, #0
ADD R0, R0, #-1
BRz BRANCH4
BRnzp BRANCH5
BRANCH4 ADD R7, R3, #0
BRnzp DATA1
BRANCH1 ADD R0, R0, #2
ADD R7, R7, R0
BRp DATA1
ADD R7, R7, #1
DATA1 BR DATA3
DATA2 BR DATA4
DATA3 BR BRANCH6
DATA4 TRAP x0
BRp BRANCH7
BRANCH6 BR BRANCH8
BR BRANCH9
BRp BRANCH10
.END
