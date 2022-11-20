;test all instructions
;
;;
;;;
.orig x4000
AND R1, R1, #0 ;r1 = 0
ADd R1, R1, #5 ; r1 = 5
AdD R1, R1, xA ; r1 = 15
aND R2, R2, x0000 ; r2 = 0
add R2, R2, r1  ; r2 = 15
BRp #1
brnZp #2
;
ld R3, #-1  ;r3 = 10239 or x27FF
ldR r4, R3, #1  ; r4 = r3 + 1
LDi r5, #1 ; r5 = men[x4000] = 第一条指令 21088 x5260
BRnzp #1;
.FILL x4000
St r5, #0   ; make next instruction be add r1,r1, #0
.FILL xF017 ; trap | r1 = 0
lD R6, #-4 ; r6 = x4000
sTr R5, R6, #-1 ; mem[x3FFF] = r5
trap x25 ;over !!!!! 
.end