.ORIG x3000
LEA R2, DATA0
AND R0, R0, #0
JSR SUB0
HALT
SUB0 STR R7, R2, #0
ADD R2, R2, #1
ADD R0, R0, #1
LD R1, DATA1
ADD R1, R5, #-1
ST R1, DATA1
BRz BRANCH0
JSR SUB0
BRANCH0 ADD R2, R2, #-1
JSR SUB1
RET
DATA0 .FILL x0
.FILL x0
.FILL x0
.FILL x0
.FILL x0
.FILL x0
.FILL x0
.FILL x0
.FILL x0
.FILL x0
DATA1 .FILL x5
.END