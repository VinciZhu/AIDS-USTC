test binaryToAscill.asm
给R0赋值987
输出：
R1: x002B   43
R2: x0039   57
R3: x0038   56
R4: x0037   55
内存：
x4000 43
x4001 57
x4002 56
x4003 55

test allInstruction.asm
要在halt处设断点，不然会改变
最终输出结果：
R0: x0000   0
R1: x0000   0
R2: x000F   15
R3: x27FF   10239
R4: x0000   0
R5: x5260   21088
R6: x4000   16384
R7: default
PC: x4010   16384
内存：
x3FFF x5260 21088

test call.asm
内存：
x4000 43
x4001 57
x4002 56
x4003 55

R0: x03DB 987

test other
应该全部出现异常，如果不出现异常，即检错机制不完备。
