.ORIG x3000

                JSR PUSH_R0
                JSR JUDGE
                JSR POP_R1
                HALT

JUDGE           ST R0, JUDGE_SAVE_R0
                ST R2, JUDGE_SAVE_R2
                ST R3, JUDGE_SAVE_R3
                ST R7, JUDGE_SAVE_R7
                
                JSR POP_R0
                AND R1, R1, #0
                ADD R1, R1, #1
                ADD R2, R1, #1
JUDGE_LOOP      JSR PUSH_R2
                JSR PUSH_R2
                JSR MUL
                JSR PUSH_R0
                JSR CMP
                JSR POP_R3
                BRp JUDGE_BREAK
                JSR PUSH_R0
                JSR PUSH_R2
                JSR MOD
                JSR POP_R3
                BRnp JUDGE_IF
                AND R1, R1, #0
                BR JUDGE_BREAK
JUDGE_IF        ADD R2, R2, #1
                BR JUDGE_LOOP
JUDGE_BREAK     JSR PUSH_R1

                LD R0, JUDGE_SAVE_R0
                LD R2, JUDGE_SAVE_R2
                LD R3, JUDGE_SAVE_R3
                LD R7, JUDGE_SAVE_R7
                RET

                JUDGE_SAVE_R0 .BLKW #1
                JUDGE_SAVE_R1 .BLKW #1
                JUDGE_SAVE_R2 .BLKW #1
                JUDGE_SAVE_R3 .BLKW #1
                JUDGE_SAVE_R7 .BLKW #1

; Subtraction
SUB             ST R0, SUB_SAVE_R0
                ST R1, SUB_SAVE_R1
                ST R7, SUB_SAVE_R7
                
                JSR POP_R1
                JSR POP_R0
                NOT R1, R1
                ADD R1, R1, #1
                ADD R0, R0, R1
                JSR PUSH_R0
                
                LD R0, SUB_SAVE_R0
                LD R1, SUB_SAVE_R1
                LD R7, SUB_SAVE_R7
                RET

SUB_SAVE_R0     .BLKW #1
SUB_SAVE_R1     .BLKW #1
SUB_SAVE_R7     .BLKW #1

; Multiplication
MUL             ST R0, MUL_SAVE_R0
                ST R1, MUL_SAVE_R1
                ST R2, MUL_SAVE_R2
                ST R3, MUL_SAVE_R3
                ST R7, MUL_SAVE_R7
                
                JSR POP_R1
                JSR POP_R0
                AND R2, R2, #0
                AND R3, R3, #0
                ADD R3, R3, #1
MUL_LOOP        AND R7, R0, R3
                BRz MUL_SKIP
                ADD R2, R2, R1
MUL_SKIP        ADD R1, R1, R1
                ADD R3, R3, R3
                BRnp MUL_LOOP
                JSR PUSH_R2
                
                LD R0, MUL_SAVE_R0
                LD R1, MUL_SAVE_R1
                LD R2, MUL_SAVE_R2
                LD R3, MUL_SAVE_R3
                LD R7, MUL_SAVE_R7
                RET

MUL_SAVE_R0     .BLKW #1
MUL_SAVE_R1     .BLKW #1
MUL_SAVE_R2     .BLKW #1
MUL_SAVE_R3     .BLKW #1
MUL_SAVE_R7     .BLKW #1

; Modulo
MOD             ST R0, MOD_SAVE_R0
                ST R1, MOD_SAVE_R1
                ST R2, MOD_SAVE_R2
                ST R3, MOD_SAVE_R3
                ST R4, MOD_SAVE_R4
                ST R7, MOD_SAVE_R7
                JSR POP_R1
                JSR POP_R0
                
                NOT R3, R1
                ADD R3, R3, #1
                AND R4, R4, #0
                ADD R4, R4, #-16
MOD_INIT_LOOP   AND R7, R0, #-1
                BRn MOD_INIT_BREAK
                ADD R0, R0, R0
                ADD R4, R4, #1
                BR MOD_INIT_LOOP
MOD_INIT_BREAK  AND R2, R2, #0
MOD_MAIN_LOOP   ADD R4, R4, #1
                BRp MOD_MAIN_BREAK
                ADD R2, R2, R2
                AND R7, R0, #-1
                BRzp MOD_SKIP 
                ADD R2, R2, #1
MOD_SKIP        JSR PUSH_R1
                JSR PUSH_R2
                JSR CMP
                JSR POP_R5
                BRp MOD_IF
                ADD R2, R2, R3
MOD_IF          ADD R0, R0, R0
                BR MOD_MAIN_LOOP
                
MOD_MAIN_BREAK  JSR PUSH_R2
                LD R0, MOD_SAVE_R0
                LD R1, MOD_SAVE_R1
                LD R2, MOD_SAVE_R2
                LD R3, MOD_SAVE_R3
                LD R4, MOD_SAVE_R4
                LD R7, MOD_SAVE_R7
                RET

MOD_SAVE_R0     .BLKW #1
MOD_SAVE_R1     .BLKW #1
MOD_SAVE_R2     .BLKW #1
MOD_SAVE_R3     .BLKW #1
MOD_SAVE_R4     .BLKW #1
MOD_SAVE_R7     .BLKW #1

; Comparison
CMP             ST R0, CMP_SAVE_R0
                ST R1, CMP_SAVE_R1
                ST R2, CMP_SAVE_R2
                ST R7, CMP_SAVE_R7
                        
                AND R2, R2, #0
                ADD R2, R2, #-1
                JSR POP_R1
                JSR POP_R0
                AND R7, R0, R1
                BRn CMP_SUB
                AND R7, R0, #-1
                BRn CMP_GREATER
                AND R7, R1, #-1
                BRn CMP_LESS
CMP_SUB         JSR PUSH_R0
                JSR PUSH_R1
                JSR SUB
                JSR POP_R0
                BRn CMP_LESS
                BRz CMP_ZERO
CMP_GREATER     ADD R2, R2, #1
CMP_ZERO        ADD R2, R2, #1
CMP_LESS        JSR PUSH_R0
                
                LD R0, CMP_SAVE_R0
                LD R1, CMP_SAVE_R1
                LD R2, CMP_SAVE_R2
                LD R7, CMP_SAVE_R7
                RET
CMP_SAVE_R0     .BLKW #1
CMP_SAVE_R1     .BLKW #1
CMP_SAVE_R2     .BLKW #1
CMP_SAVE_R7     .BLKW #1

; Stack
POP             ST R1, STACK_SAVE_R1
                ST R2, STACK_SAVE_R2
                ST R5, STACK_SAVE_R5
                ST R6, STACK_SAVE_R6
                
                LD R1, STACK_EMPTY
                LD R6, STACK_POINTER
                AND R5, R5, #0
                ADD R2, R6, R1
                BRnp POP_SUCCESS
                ADD R5, R5, #1
                BR POP_OK   
POP_SUCCESS     LDR R0, R6, #0
                ADD R6, R6, #1
POP_OK          ST R5, STACK_FAIL_FLAG
                ST R6, STACK_POINTER
                
                LD R1, STACK_SAVE_R1
                LD R2, STACK_SAVE_R2
                LD R5, STACK_SAVE_R5
                LD R6, STACK_SAVE_R6
                RET

PUSH            ST R1, STACK_SAVE_R1
                ST R2, STACK_SAVE_R2
                ST R5, STACK_SAVE_R5
                ST R6, STACK_SAVE_R6
                
                LD R1, STACK_FULL
                LD R6, STACK_POINTER
                AND R5, R5, #0
                ADD R2, R6, R1
                BRnp PUSH_SUCCESS
                ADD R5, R5, #1
                BR PUSH_OK
PUSH_SUCCESS    ADD R6, R6, #-1
                STR R0, R6, #0
PUSH_OK         ST R5, STACK_FAIL_FLAG
                ST R6, STACK_POINTER
                
                LD R1, STACK_SAVE_R1
                LD R2, STACK_SAVE_R2
                LD R5, STACK_SAVE_R5
                LD R6, STACK_SAVE_R6
                RET
                
STACK_FAIL_FLAG .FILL #0
STACK_POINTER   .FILL x4000
STACK_EMPTY     .FILL x-4000
STACK_FULL      .FILL x-3FF0
STACK_SAVE_R1   .BLKW #1
STACK_SAVE_R2   .BLKW #1
STACK_SAVE_R5   .BLKW #1
STACK_SAVE_R6   .BLKW #1

POP_R0          ST R7, STACK_R_SAVE_R7
                JSR POP
                LD R7, STACK_R_SAVE_R7
                ADD R0, R0, #0
                RET

POP_R1          ST R0, STACK_R_SAVE_R0
                ST R7, STACK_R_SAVE_R7
                JSR POP
                ADD R1, R0, #0
                LD R0, STACK_R_SAVE_R0
                LD R7, STACK_R_SAVE_R7
                ADD R1, R1, #0
                RET

POP_R2          ST R0, STACK_R_SAVE_R0
                ST R7, STACK_R_SAVE_R7
                JSR POP
                ADD R2, R0, #0
                LD R0, STACK_R_SAVE_R0
                LD R7, STACK_R_SAVE_R7
                ADD R2, R2, #0
                RET

POP_R3          ST R0, STACK_R_SAVE_R0
                ST R7, STACK_R_SAVE_R7
                JSR POP
                ADD R3, R0, #0
                LD R0, STACK_R_SAVE_R0
                LD R7, STACK_R_SAVE_R7
                ADD R3, R3, #0
                RET

POP_R4          ST R0, STACK_R_SAVE_R0
                ST R7, STACK_R_SAVE_R7
                JSR POP
                ADD R4, R0, #0
                LD R0, STACK_R_SAVE_R0
                LD R7, STACK_R_SAVE_R7
                ADD R4, R4, #0
                RET

POP_R5          ST R0, STACK_R_SAVE_R0
                ST R7, STACK_R_SAVE_R7
                JSR POP
                ADD R5, R0, #0
                LD R0, STACK_R_SAVE_R0
                LD R7, STACK_R_SAVE_R7
                ADD R5, R5, #0
                RET

POP_R6          ST R0, STACK_R_SAVE_R0
                ST R7, STACK_R_SAVE_R7
                JSR POP
                ADD R6, R0, #0
                LD R0, STACK_R_SAVE_R0
                LD R7, STACK_R_SAVE_R7
                ADD R6, R6, #0
                RET

PUSH_R0         ST R7, STACK_R_SAVE_R7
                JSR PUSH
                LD R7, STACK_R_SAVE_R7
                RET

PUSH_R1         ST R0, STACK_R_SAVE_R0
                ST R7, STACK_R_SAVE_R7
                ADD R0, R1, #0
                JSR PUSH
                LD R0, STACK_R_SAVE_R0
                LD R7, STACK_R_SAVE_R7
                RET

PUSH_R2         ST R0, STACK_R_SAVE_R0
                ST R7, STACK_R_SAVE_R7
                ADD R0, R2, #0
                JSR PUSH
                LD R0, STACK_R_SAVE_R0
                LD R7, STACK_R_SAVE_R7
                RET

PUSH_R3         ST R0, STACK_R_SAVE_R0
                ST R7, STACK_R_SAVE_R7
                ADD R0, R3, #0
                JSR PUSH
                LD R0, STACK_R_SAVE_R0
                LD R7, STACK_R_SAVE_R7
                RET

PUSH_R4         ST R0, STACK_R_SAVE_R0
                ST R7, STACK_R_SAVE_R7
                ADD R0, R4, #0
                JSR PUSH
                LD R0, STACK_R_SAVE_R0
                LD R7, STACK_R_SAVE_R7
                RET

PUSH_R5         ST R0, STACK_R_SAVE_R0
                ST R7, STACK_R_SAVE_R7
                ADD R0, R5, #0
                JSR PUSH
                LD R0, STACK_R_SAVE_R0
                LD R7, STACK_R_SAVE_R7
                RET

PUSH_R6         ST R0, STACK_R_SAVE_R0
                ST R7, STACK_R_SAVE_R7
                ADD R0, R6, #0
                JSR PUSH
                LD R0, STACK_R_SAVE_R0
                LD R7, STACK_R_SAVE_R7
                RET

STACK_R_SAVE_R0 .BLKW #1
STACK_R_SAVE_R7 .BLKW #1

.END

