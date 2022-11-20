
rtarget:	file format elf64-x86-64

Disassembly of section .init:

0000000000400c48 <_init>:
  400c48: 48 83 ec 08                  	subq	$8, %rsp
  400c4c: e8 6b 02 00 00               	callq	0x400ebc <call_gmon_start>
  400c51: 48 83 c4 08                  	addq	$8, %rsp
  400c55: c3                           	retq

Disassembly of section .plt:

0000000000400c60 <.plt>:
  400c60: ff 35 8a 43 20 00            	pushq	2114442(%rip)           # 0x604ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
  400c66: ff 25 8c 43 20 00            	jmpq	*2114444(%rip)          # 0x604ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
  400c6c: 0f 1f 40 00                  	nopl	(%rax)

0000000000400c70 <strcasecmp@plt>:
  400c70: ff 25 8a 43 20 00            	jmpq	*2114442(%rip)          # 0x605000 <_GLOBAL_OFFSET_TABLE_+0x18>
  400c76: 68 00 00 00 00               	pushq	$0
  400c7b: e9 e0 ff ff ff               	jmp	0x400c60 <.plt>

0000000000400c80 <__errno_location@plt>:
  400c80: ff 25 82 43 20 00            	jmpq	*2114434(%rip)          # 0x605008 <_GLOBAL_OFFSET_TABLE_+0x20>
  400c86: 68 01 00 00 00               	pushq	$1
  400c8b: e9 d0 ff ff ff               	jmp	0x400c60 <.plt>

0000000000400c90 <srandom@plt>:
  400c90: ff 25 7a 43 20 00            	jmpq	*2114426(%rip)          # 0x605010 <_GLOBAL_OFFSET_TABLE_+0x28>
  400c96: 68 02 00 00 00               	pushq	$2
  400c9b: e9 c0 ff ff ff               	jmp	0x400c60 <.plt>

0000000000400ca0 <strncmp@plt>:
  400ca0: ff 25 72 43 20 00            	jmpq	*2114418(%rip)          # 0x605018 <_GLOBAL_OFFSET_TABLE_+0x30>
  400ca6: 68 03 00 00 00               	pushq	$3
  400cab: e9 b0 ff ff ff               	jmp	0x400c60 <.plt>

0000000000400cb0 <strcpy@plt>:
  400cb0: ff 25 6a 43 20 00            	jmpq	*2114410(%rip)          # 0x605020 <_GLOBAL_OFFSET_TABLE_+0x38>
  400cb6: 68 04 00 00 00               	pushq	$4
  400cbb: e9 a0 ff ff ff               	jmp	0x400c60 <.plt>

0000000000400cc0 <puts@plt>:
  400cc0: ff 25 62 43 20 00            	jmpq	*2114402(%rip)          # 0x605028 <_GLOBAL_OFFSET_TABLE_+0x40>
  400cc6: 68 05 00 00 00               	pushq	$5
  400ccb: e9 90 ff ff ff               	jmp	0x400c60 <.plt>

0000000000400cd0 <write@plt>:
  400cd0: ff 25 5a 43 20 00            	jmpq	*2114394(%rip)          # 0x605030 <_GLOBAL_OFFSET_TABLE_+0x48>
  400cd6: 68 06 00 00 00               	pushq	$6
  400cdb: e9 80 ff ff ff               	jmp	0x400c60 <.plt>

0000000000400ce0 <__stack_chk_fail@plt>:
  400ce0: ff 25 52 43 20 00            	jmpq	*2114386(%rip)          # 0x605038 <_GLOBAL_OFFSET_TABLE_+0x50>
  400ce6: 68 07 00 00 00               	pushq	$7
  400ceb: e9 70 ff ff ff               	jmp	0x400c60 <.plt>

0000000000400cf0 <mmap@plt>:
  400cf0: ff 25 4a 43 20 00            	jmpq	*2114378(%rip)          # 0x605040 <_GLOBAL_OFFSET_TABLE_+0x58>
  400cf6: 68 08 00 00 00               	pushq	$8
  400cfb: e9 60 ff ff ff               	jmp	0x400c60 <.plt>

0000000000400d00 <memset@plt>:
  400d00: ff 25 42 43 20 00            	jmpq	*2114370(%rip)          # 0x605048 <_GLOBAL_OFFSET_TABLE_+0x60>
  400d06: 68 09 00 00 00               	pushq	$9
  400d0b: e9 50 ff ff ff               	jmp	0x400c60 <.plt>

0000000000400d10 <alarm@plt>:
  400d10: ff 25 3a 43 20 00            	jmpq	*2114362(%rip)          # 0x605050 <_GLOBAL_OFFSET_TABLE_+0x68>
  400d16: 68 0a 00 00 00               	pushq	$10
  400d1b: e9 40 ff ff ff               	jmp	0x400c60 <.plt>

0000000000400d20 <close@plt>:
  400d20: ff 25 32 43 20 00            	jmpq	*2114354(%rip)          # 0x605058 <_GLOBAL_OFFSET_TABLE_+0x70>
  400d26: 68 0b 00 00 00               	pushq	$11
  400d2b: e9 30 ff ff ff               	jmp	0x400c60 <.plt>

0000000000400d30 <read@plt>:
  400d30: ff 25 2a 43 20 00            	jmpq	*2114346(%rip)          # 0x605060 <_GLOBAL_OFFSET_TABLE_+0x78>
  400d36: 68 0c 00 00 00               	pushq	$12
  400d3b: e9 20 ff ff ff               	jmp	0x400c60 <.plt>

0000000000400d40 <__libc_start_main@plt>:
  400d40: ff 25 22 43 20 00            	jmpq	*2114338(%rip)          # 0x605068 <_GLOBAL_OFFSET_TABLE_+0x80>
  400d46: 68 0d 00 00 00               	pushq	$13
  400d4b: e9 10 ff ff ff               	jmp	0x400c60 <.plt>

0000000000400d50 <signal@plt>:
  400d50: ff 25 1a 43 20 00            	jmpq	*2114330(%rip)          # 0x605070 <_GLOBAL_OFFSET_TABLE_+0x88>
  400d56: 68 0e 00 00 00               	pushq	$14
  400d5b: e9 00 ff ff ff               	jmp	0x400c60 <.plt>

0000000000400d60 <gethostbyname@plt>:
  400d60: ff 25 12 43 20 00            	jmpq	*2114322(%rip)          # 0x605078 <_GLOBAL_OFFSET_TABLE_+0x90>
  400d66: 68 0f 00 00 00               	pushq	$15
  400d6b: e9 f0 fe ff ff               	jmp	0x400c60 <.plt>

0000000000400d70 <__memmove_chk@plt>:
  400d70: ff 25 0a 43 20 00            	jmpq	*2114314(%rip)          # 0x605080 <_GLOBAL_OFFSET_TABLE_+0x98>
  400d76: 68 10 00 00 00               	pushq	$16
  400d7b: e9 e0 fe ff ff               	jmp	0x400c60 <.plt>

0000000000400d80 <strtol@plt>:
  400d80: ff 25 02 43 20 00            	jmpq	*2114306(%rip)          # 0x605088 <_GLOBAL_OFFSET_TABLE_+0xa0>
  400d86: 68 11 00 00 00               	pushq	$17
  400d8b: e9 d0 fe ff ff               	jmp	0x400c60 <.plt>

0000000000400d90 <memcpy@plt>:
  400d90: ff 25 fa 42 20 00            	jmpq	*2114298(%rip)          # 0x605090 <_GLOBAL_OFFSET_TABLE_+0xa8>
  400d96: 68 12 00 00 00               	pushq	$18
  400d9b: e9 c0 fe ff ff               	jmp	0x400c60 <.plt>

0000000000400da0 <time@plt>:
  400da0: ff 25 f2 42 20 00            	jmpq	*2114290(%rip)          # 0x605098 <_GLOBAL_OFFSET_TABLE_+0xb0>
  400da6: 68 13 00 00 00               	pushq	$19
  400dab: e9 b0 fe ff ff               	jmp	0x400c60 <.plt>

0000000000400db0 <random@plt>:
  400db0: ff 25 ea 42 20 00            	jmpq	*2114282(%rip)          # 0x6050a0 <_GLOBAL_OFFSET_TABLE_+0xb8>
  400db6: 68 14 00 00 00               	pushq	$20
  400dbb: e9 a0 fe ff ff               	jmp	0x400c60 <.plt>

0000000000400dc0 <_IO_getc@plt>:
  400dc0: ff 25 e2 42 20 00            	jmpq	*2114274(%rip)          # 0x6050a8 <_GLOBAL_OFFSET_TABLE_+0xc0>
  400dc6: 68 15 00 00 00               	pushq	$21
  400dcb: e9 90 fe ff ff               	jmp	0x400c60 <.plt>

0000000000400dd0 <__isoc99_sscanf@plt>:
  400dd0: ff 25 da 42 20 00            	jmpq	*2114266(%rip)          # 0x6050b0 <_GLOBAL_OFFSET_TABLE_+0xc8>
  400dd6: 68 16 00 00 00               	pushq	$22
  400ddb: e9 80 fe ff ff               	jmp	0x400c60 <.plt>

0000000000400de0 <munmap@plt>:
  400de0: ff 25 d2 42 20 00            	jmpq	*2114258(%rip)          # 0x6050b8 <_GLOBAL_OFFSET_TABLE_+0xd0>
  400de6: 68 17 00 00 00               	pushq	$23
  400deb: e9 70 fe ff ff               	jmp	0x400c60 <.plt>

0000000000400df0 <__printf_chk@plt>:
  400df0: ff 25 ca 42 20 00            	jmpq	*2114250(%rip)          # 0x6050c0 <_GLOBAL_OFFSET_TABLE_+0xd8>
  400df6: 68 18 00 00 00               	pushq	$24
  400dfb: e9 60 fe ff ff               	jmp	0x400c60 <.plt>

0000000000400e00 <fopen@plt>:
  400e00: ff 25 c2 42 20 00            	jmpq	*2114242(%rip)          # 0x6050c8 <_GLOBAL_OFFSET_TABLE_+0xe0>
  400e06: 68 19 00 00 00               	pushq	$25
  400e0b: e9 50 fe ff ff               	jmp	0x400c60 <.plt>

0000000000400e10 <getopt@plt>:
  400e10: ff 25 ba 42 20 00            	jmpq	*2114234(%rip)          # 0x6050d0 <_GLOBAL_OFFSET_TABLE_+0xe8>
  400e16: 68 1a 00 00 00               	pushq	$26
  400e1b: e9 40 fe ff ff               	jmp	0x400c60 <.plt>

0000000000400e20 <strtoul@plt>:
  400e20: ff 25 b2 42 20 00            	jmpq	*2114226(%rip)          # 0x6050d8 <_GLOBAL_OFFSET_TABLE_+0xf0>
  400e26: 68 1b 00 00 00               	pushq	$27
  400e2b: e9 30 fe ff ff               	jmp	0x400c60 <.plt>

0000000000400e30 <gethostname@plt>:
  400e30: ff 25 aa 42 20 00            	jmpq	*2114218(%rip)          # 0x6050e0 <_GLOBAL_OFFSET_TABLE_+0xf8>
  400e36: 68 1c 00 00 00               	pushq	$28
  400e3b: e9 20 fe ff ff               	jmp	0x400c60 <.plt>

0000000000400e40 <exit@plt>:
  400e40: ff 25 a2 42 20 00            	jmpq	*2114210(%rip)          # 0x6050e8 <_GLOBAL_OFFSET_TABLE_+0x100>
  400e46: 68 1d 00 00 00               	pushq	$29
  400e4b: e9 10 fe ff ff               	jmp	0x400c60 <.plt>

0000000000400e50 <connect@plt>:
  400e50: ff 25 9a 42 20 00            	jmpq	*2114202(%rip)          # 0x6050f0 <_GLOBAL_OFFSET_TABLE_+0x108>
  400e56: 68 1e 00 00 00               	pushq	$30
  400e5b: e9 00 fe ff ff               	jmp	0x400c60 <.plt>

0000000000400e60 <__fprintf_chk@plt>:
  400e60: ff 25 92 42 20 00            	jmpq	*2114194(%rip)          # 0x6050f8 <_GLOBAL_OFFSET_TABLE_+0x110>
  400e66: 68 1f 00 00 00               	pushq	$31
  400e6b: e9 f0 fd ff ff               	jmp	0x400c60 <.plt>

0000000000400e70 <__sprintf_chk@plt>:
  400e70: ff 25 8a 42 20 00            	jmpq	*2114186(%rip)          # 0x605100 <_GLOBAL_OFFSET_TABLE_+0x118>
  400e76: 68 20 00 00 00               	pushq	$32
  400e7b: e9 e0 fd ff ff               	jmp	0x400c60 <.plt>

0000000000400e80 <socket@plt>:
  400e80: ff 25 82 42 20 00            	jmpq	*2114178(%rip)          # 0x605108 <_GLOBAL_OFFSET_TABLE_+0x120>
  400e86: 68 21 00 00 00               	pushq	$33
  400e8b: e9 d0 fd ff ff               	jmp	0x400c60 <.plt>

Disassembly of section .text:

0000000000400e90 <_start>:
  400e90: 31 ed                        	xorl	%ebp, %ebp
  400e92: 49 89 d1                     	movq	%rdx, %r9
  400e95: 5e                           	popq	%rsi
  400e96: 48 89 e2                     	movq	%rsp, %rdx
  400e99: 48 83 e4 f0                  	andq	$-16, %rsp
  400e9d: 50                           	pushq	%rax
  400e9e: 54                           	pushq	%rsp
  400e9f: 49 c7 c0 90 2e 40 00         	movq	$4206224, %r8           # imm = 0x402E90
  400ea6: 48 c7 c1 00 2e 40 00         	movq	$4206080, %rcx          # imm = 0x402E00
  400ead: 48 c7 c7 ad 11 40 00         	movq	$4198829, %rdi          # imm = 0x4011AD
  400eb4: e8 87 fe ff ff               	callq	0x400d40 <__libc_start_main@plt>
  400eb9: f4                           	hlt
  400eba: 90                           	nop
  400ebb: 90                           	nop

0000000000400ebc <call_gmon_start>:
  400ebc: 48 83 ec 08                  	subq	$8, %rsp
  400ec0: 48 8b 05 19 41 20 00         	movq	2113817(%rip), %rax     # 0x604fe0 <write@@GLIBC_2.2.5+0x604fe0>
  400ec7: 48 85 c0                     	testq	%rax, %rax
  400eca: 74 02                        	je	0x400ece <call_gmon_start+0x12>
  400ecc: ff d0                        	callq	*%rax
  400ece: 48 83 c4 08                  	addq	$8, %rsp
  400ed2: c3                           	retq
  400ed3: 90                           	nop
  400ed4: 90                           	nop
  400ed5: 90                           	nop
  400ed6: 90                           	nop
  400ed7: 90                           	nop
  400ed8: 90                           	nop
  400ed9: 90                           	nop
  400eda: 90                           	nop
  400edb: 90                           	nop
  400edc: 90                           	nop
  400edd: 90                           	nop
  400ede: 90                           	nop
  400edf: 90                           	nop

0000000000400ee0 <deregister_tm_clones>:
  400ee0: b8 97 54 60 00               	movl	$6313111, %eax          # imm = 0x605497
  400ee5: 55                           	pushq	%rbp
  400ee6: 48 2d 90 54 60 00            	subq	$6313104, %rax          # imm = 0x605490
  400eec: 48 83 f8 0e                  	cmpq	$14, %rax
  400ef0: 48 89 e5                     	movq	%rsp, %rbp
  400ef3: 77 02                        	ja	0x400ef7 <deregister_tm_clones+0x17>
  400ef5: 5d                           	popq	%rbp
  400ef6: c3                           	retq
  400ef7: b8 00 00 00 00               	movl	$0, %eax
  400efc: 48 85 c0                     	testq	%rax, %rax
  400eff: 74 f4                        	je	0x400ef5 <deregister_tm_clones+0x15>
  400f01: 5d                           	popq	%rbp
  400f02: bf 90 54 60 00               	movl	$6313104, %edi          # imm = 0x605490
  400f07: ff e0                        	jmpq	*%rax
  400f09: 0f 1f 80 00 00 00 00         	nopl	(%rax)

0000000000400f10 <register_tm_clones>:
  400f10: b8 90 54 60 00               	movl	$6313104, %eax          # imm = 0x605490
  400f15: 55                           	pushq	%rbp
  400f16: 48 2d 90 54 60 00            	subq	$6313104, %rax          # imm = 0x605490
  400f1c: 48 c1 f8 03                  	sarq	$3, %rax
  400f20: 48 89 e5                     	movq	%rsp, %rbp
  400f23: 48 89 c2                     	movq	%rax, %rdx
  400f26: 48 c1 ea 3f                  	shrq	$63, %rdx
  400f2a: 48 01 d0                     	addq	%rdx, %rax
  400f2d: 48 d1 f8                     	sarq	%rax
  400f30: 75 02                        	jne	0x400f34 <register_tm_clones+0x24>
  400f32: 5d                           	popq	%rbp
  400f33: c3                           	retq
  400f34: ba 00 00 00 00               	movl	$0, %edx
  400f39: 48 85 d2                     	testq	%rdx, %rdx
  400f3c: 74 f4                        	je	0x400f32 <register_tm_clones+0x22>
  400f3e: 5d                           	popq	%rbp
  400f3f: 48 89 c6                     	movq	%rax, %rsi
  400f42: bf 90 54 60 00               	movl	$6313104, %edi          # imm = 0x605490
  400f47: ff e2                        	jmpq	*%rdx
  400f49: 0f 1f 80 00 00 00 00         	nopl	(%rax)

0000000000400f50 <__do_global_dtors_aux>:
  400f50: 80 3d 61 45 20 00 00         	cmpb	$0, 2114913(%rip)       # 0x6054b8 <completed.6976>
  400f57: 75 11                        	jne	0x400f6a <__do_global_dtors_aux+0x1a>
  400f59: 55                           	pushq	%rbp
  400f5a: 48 89 e5                     	movq	%rsp, %rbp
  400f5d: e8 7e ff ff ff               	callq	0x400ee0 <deregister_tm_clones>
  400f62: 5d                           	popq	%rbp
  400f63: c6 05 4e 45 20 00 01         	movb	$1, 2114894(%rip)       # 0x6054b8 <completed.6976>
  400f6a: f3 c3                        	rep		retq
  400f6c: 0f 1f 40 00                  	nopl	(%rax)

0000000000400f70 <frame_dummy>:
  400f70: 48 83 3d 90 3e 20 00 00      	cmpq	$0, 2113168(%rip)       # 0x604e08 <__JCR_LIST__>
  400f78: 74 1e                        	je	0x400f98 <frame_dummy+0x28>
  400f7a: b8 00 00 00 00               	movl	$0, %eax
  400f7f: 48 85 c0                     	testq	%rax, %rax
  400f82: 74 14                        	je	0x400f98 <frame_dummy+0x28>
  400f84: 55                           	pushq	%rbp
  400f85: bf 08 4e 60 00               	movl	$6311432, %edi          # imm = 0x604E08
  400f8a: 48 89 e5                     	movq	%rsp, %rbp
  400f8d: ff d0                        	callq	*%rax
  400f8f: 5d                           	popq	%rbp
  400f90: e9 7b ff ff ff               	jmp	0x400f10 <register_tm_clones>
  400f95: 0f 1f 00                     	nopl	(%rax)
  400f98: e9 73 ff ff ff               	jmp	0x400f10 <register_tm_clones>
  400f9d: 90                           	nop
  400f9e: 90                           	nop
  400f9f: 90                           	nop

0000000000400fa0 <usage>:
  400fa0: 48 83 ec 08                  	subq	$8, %rsp
  400fa4: 48 89 fa                     	movq	%rdi, %rdx
  400fa7: 83 3d 3a 45 20 00 00         	cmpl	$0, 2114874(%rip)       # 0x6054e8 <is_checker>
  400fae: 74 3e                        	je	0x400fee <usage+0x4e>
  400fb0: be a8 2e 40 00               	movl	$4206248, %esi          # imm = 0x402EA8
  400fb5: bf 01 00 00 00               	movl	$1, %edi
  400fba: b8 00 00 00 00               	movl	$0, %eax
  400fbf: e8 2c fe ff ff               	callq	0x400df0 <__printf_chk@plt>
  400fc4: bf e0 2e 40 00               	movl	$4206304, %edi          # imm = 0x402EE0
  400fc9: e8 f2 fc ff ff               	callq	0x400cc0 <puts@plt>
  400fce: bf 58 30 40 00               	movl	$4206680, %edi          # imm = 0x403058
  400fd3: e8 e8 fc ff ff               	callq	0x400cc0 <puts@plt>
  400fd8: bf 08 2f 40 00               	movl	$4206344, %edi          # imm = 0x402F08
  400fdd: e8 de fc ff ff               	callq	0x400cc0 <puts@plt>
  400fe2: bf 72 30 40 00               	movl	$4206706, %edi          # imm = 0x403072
  400fe7: e8 d4 fc ff ff               	callq	0x400cc0 <puts@plt>
  400fec: eb 32                        	jmp	0x401020 <usage+0x80>
  400fee: be 8e 30 40 00               	movl	$4206734, %esi          # imm = 0x40308E
  400ff3: bf 01 00 00 00               	movl	$1, %edi
  400ff8: b8 00 00 00 00               	movl	$0, %eax
  400ffd: e8 ee fd ff ff               	callq	0x400df0 <__printf_chk@plt>
  401002: bf 30 2f 40 00               	movl	$4206384, %edi          # imm = 0x402F30
  401007: e8 b4 fc ff ff               	callq	0x400cc0 <puts@plt>
  40100c: bf 58 2f 40 00               	movl	$4206424, %edi          # imm = 0x402F58
  401011: e8 aa fc ff ff               	callq	0x400cc0 <puts@plt>
  401016: bf ac 30 40 00               	movl	$4206764, %edi          # imm = 0x4030AC
  40101b: e8 a0 fc ff ff               	callq	0x400cc0 <puts@plt>
  401020: bf 00 00 00 00               	movl	$0, %edi
  401025: e8 16 fe ff ff               	callq	0x400e40 <exit@plt>

000000000040102a <initialize_target>:
  40102a: 55                           	pushq	%rbp
  40102b: 53                           	pushq	%rbx
  40102c: 48 81 ec 18 21 00 00         	subq	$8472, %rsp             # imm = 0x2118
  401033: 89 f5                        	movl	%esi, %ebp
  401035: 64 48 8b 04 25 28 00 00 00   	movq	%fs:40, %rax
  40103e: 48 89 84 24 08 21 00 00      	movq	%rax, 8456(%rsp)
  401046: 31 c0                        	xorl	%eax, %eax
  401048: 89 3d 8a 44 20 00            	movl	%edi, 2114698(%rip)     # 0x6054d8 <check_level>
  40104e: 8b 3d f4 40 20 00            	movl	2113780(%rip), %edi     # 0x605148 <target_id>
  401054: e8 85 1d 00 00               	callq	0x402dde <gencookie>
  401059: 89 05 85 44 20 00            	movl	%eax, 2114693(%rip)     # 0x6054e4 <cookie>
  40105f: 89 c7                        	movl	%eax, %edi
  401061: e8 78 1d 00 00               	callq	0x402dde <gencookie>
  401066: 89 05 74 44 20 00            	movl	%eax, 2114676(%rip)     # 0x6054e0 <authkey>
  40106c: 8b 05 d6 40 20 00            	movl	2113750(%rip), %eax     # 0x605148 <target_id>
  401072: 8d 78 01                     	leal	1(%rax), %edi
  401075: e8 16 fc ff ff               	callq	0x400c90 <srandom@plt>
  40107a: e8 31 fd ff ff               	callq	0x400db0 <random@plt>
  40107f: 89 c7                        	movl	%eax, %edi
  401081: e8 02 03 00 00               	callq	0x401388 <scramble>
  401086: 89 c3                        	movl	%eax, %ebx
  401088: ba 00 00 00 00               	movl	$0, %edx
  40108d: 85 ed                        	testl	%ebp, %ebp
  40108f: 74 18                        	je	0x4010a9 <initialize_target+0x7f>
  401091: bf 00 00 00 00               	movl	$0, %edi
  401096: e8 05 fd ff ff               	callq	0x400da0 <time@plt>
  40109b: 89 c7                        	movl	%eax, %edi
  40109d: e8 ee fb ff ff               	callq	0x400c90 <srandom@plt>
  4010a2: e8 09 fd ff ff               	callq	0x400db0 <random@plt>
  4010a7: 89 c2                        	movl	%eax, %edx
  4010a9: 01 da                        	addl	%ebx, %edx
  4010ab: 0f b7 d2                     	movzwl	%dx, %edx
  4010ae: 8d 04 d5 00 01 00 00         	leal	256(,%rdx,8), %eax
  4010b5: 89 c0                        	movl	%eax, %eax
  4010b7: 48 89 05 c2 43 20 00         	movq	%rax, 2114498(%rip)     # 0x605480 <buf_offset>
  4010be: c6 05 43 50 20 00 72         	movb	$114, 2117699(%rip)     # 0x606108 <target_prefix>
  4010c5: 83 3d bc 43 20 00 00         	cmpl	$0, 2114492(%rip)       # 0x605488 <notify>
  4010cc: 0f 84 b9 00 00 00            	je	0x40118b <initialize_target+0x161>
  4010d2: 83 3d 0f 44 20 00 00         	cmpl	$0, 2114575(%rip)       # 0x6054e8 <is_checker>
  4010d9: 0f 85 ac 00 00 00            	jne	0x40118b <initialize_target+0x161>
  4010df: be 00 01 00 00               	movl	$256, %esi              # imm = 0x100
  4010e4: 48 89 e7                     	movq	%rsp, %rdi
  4010e7: e8 44 fd ff ff               	callq	0x400e30 <gethostname@plt>
  4010ec: bb 00 00 00 00               	movl	$0, %ebx
  4010f1: 85 c0                        	testl	%eax, %eax
  4010f3: 74 23                        	je	0x401118 <initialize_target+0xee>
  4010f5: bf 88 2f 40 00               	movl	$4206472, %edi          # imm = 0x402F88
  4010fa: e8 c1 fb ff ff               	callq	0x400cc0 <puts@plt>
  4010ff: bf 08 00 00 00               	movl	$8, %edi
  401104: e8 37 fd ff ff               	callq	0x400e40 <exit@plt>
  401109: 48 89 e6                     	movq	%rsp, %rsi
  40110c: e8 5f fb ff ff               	callq	0x400c70 <strcasecmp@plt>
  401111: 85 c0                        	testl	%eax, %eax
  401113: 74 1a                        	je	0x40112f <initialize_target+0x105>
  401115: 83 c3 01                     	addl	$1, %ebx
  401118: 48 63 c3                     	movslq	%ebx, %rax
  40111b: 48 8b 3c c5 60 51 60 00      	movq	6312288(,%rax,8), %rdi
  401123: 48 85 ff                     	testq	%rdi, %rdi
  401126: 75 e1                        	jne	0x401109 <initialize_target+0xdf>
  401128: b8 00 00 00 00               	movl	$0, %eax
  40112d: eb 05                        	jmp	0x401134 <initialize_target+0x10a>
  40112f: b8 01 00 00 00               	movl	$1, %eax
  401134: 85 c0                        	testl	%eax, %eax
  401136: 75 1c                        	jne	0x401154 <initialize_target+0x12a>
  401138: 48 89 e2                     	movq	%rsp, %rdx
  40113b: be c0 2f 40 00               	movl	$4206528, %esi          # imm = 0x402FC0
  401140: bf 01 00 00 00               	movl	$1, %edi
  401145: e8 a6 fc ff ff               	callq	0x400df0 <__printf_chk@plt>
  40114a: bf 08 00 00 00               	movl	$8, %edi
  40114f: e8 ec fc ff ff               	callq	0x400e40 <exit@plt>
  401154: 48 8d bc 24 00 01 00 00      	leaq	256(%rsp), %rdi
  40115c: e8 e3 19 00 00               	callq	0x402b44 <init_driver>
  401161: 85 c0                        	testl	%eax, %eax
  401163: 79 26                        	jns	0x40118b <initialize_target+0x161>
  401165: 48 8d 94 24 00 01 00 00      	leaq	256(%rsp), %rdx
  40116d: be 00 30 40 00               	movl	$4206592, %esi          # imm = 0x403000
  401172: bf 01 00 00 00               	movl	$1, %edi
  401177: b8 00 00 00 00               	movl	$0, %eax
  40117c: e8 6f fc ff ff               	callq	0x400df0 <__printf_chk@plt>
  401181: bf 08 00 00 00               	movl	$8, %edi
  401186: e8 b5 fc ff ff               	callq	0x400e40 <exit@plt>
  40118b: 48 8b 84 24 08 21 00 00      	movq	8456(%rsp), %rax
  401193: 64 48 33 04 25 28 00 00 00   	xorq	%fs:40, %rax
  40119c: 74 05                        	je	0x4011a3 <initialize_target+0x179>
  40119e: e8 3d fb ff ff               	callq	0x400ce0 <__stack_chk_fail@plt>
  4011a3: 48 81 c4 18 21 00 00         	addq	$8472, %rsp             # imm = 0x2118
  4011aa: 5b                           	popq	%rbx
  4011ab: 5d                           	popq	%rbp
  4011ac: c3                           	retq

00000000004011ad <main>:
  4011ad: 41 56                        	pushq	%r14
  4011af: 41 55                        	pushq	%r13
  4011b1: 41 54                        	pushq	%r12
  4011b3: 55                           	pushq	%rbp
  4011b4: 53                           	pushq	%rbx
  4011b5: 41 89 fc                     	movl	%edi, %r12d
  4011b8: 48 89 f3                     	movq	%rsi, %rbx
  4011bb: be e5 1e 40 00               	movl	$4202213, %esi          # imm = 0x401EE5
  4011c0: bf 0b 00 00 00               	movl	$11, %edi
  4011c5: e8 86 fb ff ff               	callq	0x400d50 <signal@plt>
  4011ca: be 97 1e 40 00               	movl	$4202135, %esi          # imm = 0x401E97
  4011cf: bf 07 00 00 00               	movl	$7, %edi
  4011d4: e8 77 fb ff ff               	callq	0x400d50 <signal@plt>
  4011d9: be 33 1f 40 00               	movl	$4202291, %esi          # imm = 0x401F33
  4011de: bf 04 00 00 00               	movl	$4, %edi
  4011e3: e8 68 fb ff ff               	callq	0x400d50 <signal@plt>
  4011e8: bd c5 30 40 00               	movl	$4206789, %ebp          # imm = 0x4030C5
  4011ed: 83 3d f4 42 20 00 00         	cmpl	$0, 2114292(%rip)       # 0x6054e8 <is_checker>
  4011f4: 74 1e                        	je	0x401214 <main+0x67>
  4011f6: be 81 1f 40 00               	movl	$4202369, %esi          # imm = 0x401F81
  4011fb: bf 0e 00 00 00               	movl	$14, %edi
  401200: e8 4b fb ff ff               	callq	0x400d50 <signal@plt>
  401205: bf 05 00 00 00               	movl	$5, %edi
  40120a: e8 01 fb ff ff               	callq	0x400d10 <alarm@plt>
  40120f: bd ca 30 40 00               	movl	$4206794, %ebp          # imm = 0x4030CA
  401214: 48 8b 05 85 42 20 00         	movq	2114181(%rip), %rax     # 0x6054a0 <stdin@@GLIBC_2.2.5>
  40121b: 48 89 05 ae 42 20 00         	movq	%rax, 2114222(%rip)     # 0x6054d0 <infile>
  401222: 41 bd 00 00 00 00            	movl	$0, %r13d
  401228: 41 be 00 00 00 00            	movl	$0, %r14d
  40122e: e9 c6 00 00 00               	jmp	0x4012f9 <main+0x14c>
  401233: 83 e8 61                     	subl	$97, %eax
  401236: 3c 10                        	cmpb	$16, %al
  401238: 0f 87 9c 00 00 00            	ja	0x4012da <main+0x12d>
  40123e: 0f b6 c0                     	movzbl	%al, %eax
  401241: ff 24 c5 10 31 40 00         	jmpq	*4206864(,%rax,8)
  401248: 48 8b 3b                     	movq	(%rbx), %rdi
  40124b: e8 50 fd ff ff               	callq	0x400fa0 <usage>
  401250: be 8d 33 40 00               	movl	$4207501, %esi          # imm = 0x40338D
  401255: 48 8b 3d 4c 42 20 00         	movq	2114124(%rip), %rdi     # 0x6054a8 <optarg@@GLIBC_2.2.5>
  40125c: e8 9f fb ff ff               	callq	0x400e00 <fopen@plt>
  401261: 48 89 05 68 42 20 00         	movq	%rax, 2114152(%rip)     # 0x6054d0 <infile>
  401268: 48 85 c0                     	testq	%rax, %rax
  40126b: 0f 85 88 00 00 00            	jne	0x4012f9 <main+0x14c>
  401271: 48 8b 0d 30 42 20 00         	movq	2114096(%rip), %rcx     # 0x6054a8 <optarg@@GLIBC_2.2.5>
  401278: ba d2 30 40 00               	movl	$4206802, %edx          # imm = 0x4030D2
  40127d: be 01 00 00 00               	movl	$1, %esi
  401282: 48 8b 3d 27 42 20 00         	movq	2114087(%rip), %rdi     # 0x6054b0 <stderr@@GLIBC_2.2.5>
  401289: e8 d2 fb ff ff               	callq	0x400e60 <__fprintf_chk@plt>
  40128e: b8 01 00 00 00               	movl	$1, %eax
  401293: e9 e4 00 00 00               	jmp	0x40137c <main+0x1cf>
  401298: ba 10 00 00 00               	movl	$16, %edx
  40129d: be 00 00 00 00               	movl	$0, %esi
  4012a2: 48 8b 3d ff 41 20 00         	movq	2114047(%rip), %rdi     # 0x6054a8 <optarg@@GLIBC_2.2.5>
  4012a9: e8 72 fb ff ff               	callq	0x400e20 <strtoul@plt>
  4012ae: 41 89 c6                     	movl	%eax, %r14d
  4012b1: eb 46                        	jmp	0x4012f9 <main+0x14c>
  4012b3: ba 0a 00 00 00               	movl	$10, %edx
  4012b8: be 00 00 00 00               	movl	$0, %esi
  4012bd: 48 8b 3d e4 41 20 00         	movq	2114020(%rip), %rdi     # 0x6054a8 <optarg@@GLIBC_2.2.5>
  4012c4: e8 b7 fa ff ff               	callq	0x400d80 <strtol@plt>
  4012c9: 41 89 c5                     	movl	%eax, %r13d
  4012cc: eb 2b                        	jmp	0x4012f9 <main+0x14c>
  4012ce: c7 05 b0 41 20 00 00 00 00 00	movl	$0, 2113968(%rip)       # 0x605488 <notify>
  4012d8: eb 1f                        	jmp	0x4012f9 <main+0x14c>
  4012da: 0f be d2                     	movsbl	%dl, %edx
  4012dd: be ef 30 40 00               	movl	$4206831, %esi          # imm = 0x4030EF
  4012e2: bf 01 00 00 00               	movl	$1, %edi
  4012e7: b8 00 00 00 00               	movl	$0, %eax
  4012ec: e8 ff fa ff ff               	callq	0x400df0 <__printf_chk@plt>
  4012f1: 48 8b 3b                     	movq	(%rbx), %rdi
  4012f4: e8 a7 fc ff ff               	callq	0x400fa0 <usage>
  4012f9: 48 89 ea                     	movq	%rbp, %rdx
  4012fc: 48 89 de                     	movq	%rbx, %rsi
  4012ff: 44 89 e7                     	movl	%r12d, %edi
  401302: e8 09 fb ff ff               	callq	0x400e10 <getopt@plt>
  401307: 89 c2                        	movl	%eax, %edx
  401309: 3c ff                        	cmpb	$-1, %al
  40130b: 0f 85 22 ff ff ff            	jne	0x401233 <main+0x86>
  401311: be 01 00 00 00               	movl	$1, %esi
  401316: 44 89 ef                     	movl	%r13d, %edi
  401319: e8 0c fd ff ff               	callq	0x40102a <initialize_target>
  40131e: 83 3d c3 41 20 00 00         	cmpl	$0, 2113987(%rip)       # 0x6054e8 <is_checker>
  401325: 74 2a                        	je	0x401351 <main+0x1a4>
  401327: 44 3b 35 b2 41 20 00         	cmpl	2113970(%rip), %r14d    # 0x6054e0 <authkey>
  40132e: 74 21                        	je	0x401351 <main+0x1a4>
  401330: 44 89 f2                     	movl	%r14d, %edx
  401333: be 28 30 40 00               	movl	$4206632, %esi          # imm = 0x403028
  401338: bf 01 00 00 00               	movl	$1, %edi
  40133d: b8 00 00 00 00               	movl	$0, %eax
  401342: e8 a9 fa ff ff               	callq	0x400df0 <__printf_chk@plt>
  401347: b8 00 00 00 00               	movl	$0, %eax
  40134c: e8 da 07 00 00               	callq	0x401b2b <check_fail>
  401351: 8b 15 8d 41 20 00            	movl	2113933(%rip), %edx     # 0x6054e4 <cookie>
  401357: be 02 31 40 00               	movl	$4206850, %esi          # imm = 0x403102
  40135c: bf 01 00 00 00               	movl	$1, %edi
  401361: b8 00 00 00 00               	movl	$0, %eax
  401366: e8 85 fa ff ff               	callq	0x400df0 <__printf_chk@plt>
  40136b: 48 8b 3d 0e 41 20 00         	movq	2113806(%rip), %rdi     # 0x605480 <buf_offset>
  401372: e8 5d 0c 00 00               	callq	0x401fd4 <launch>
  401377: b8 00 00 00 00               	movl	$0, %eax
  40137c: 5b                           	popq	%rbx
  40137d: 5d                           	popq	%rbp
  40137e: 41 5c                        	popq	%r12
  401380: 41 5d                        	popq	%r13
  401382: 41 5e                        	popq	%r14
  401384: c3                           	retq
  401385: 90                           	nop
  401386: 90                           	nop
  401387: 90                           	nop

0000000000401388 <scramble>:
  401388: b8 00 00 00 00               	movl	$0, %eax
  40138d: eb 11                        	jmp	0x4013a0 <scramble+0x18>
  40138f: 69 c8 7f 79 00 00            	imull	$31103, %eax, %ecx      # imm = 0x797F
  401395: 01 f9                        	addl	%edi, %ecx
  401397: 89 c2                        	movl	%eax, %edx
  401399: 89 4c 94 c8                  	movl	%ecx, -56(%rsp,%rdx,4)
  40139d: 83 c0 01                     	addl	$1, %eax
  4013a0: 83 f8 09                     	cmpl	$9, %eax
  4013a3: 76 ea                        	jbe	0x40138f <scramble+0x7>
  4013a5: 8b 44 24 dc                  	movl	-36(%rsp), %eax
  4013a9: 69 c0 44 a6 00 00            	imull	$42564, %eax, %eax      # imm = 0xA644
  4013af: 89 44 24 dc                  	movl	%eax, -36(%rsp)
  4013b3: 8b 44 24 e8                  	movl	-24(%rsp), %eax
  4013b7: 69 c0 d5 50 00 00            	imull	$20693, %eax, %eax      # imm = 0x50D5
  4013bd: 89 44 24 e8                  	movl	%eax, -24(%rsp)
  4013c1: 8b 44 24 e4                  	movl	-28(%rsp), %eax
  4013c5: 69 c0 00 3a 00 00            	imull	$14848, %eax, %eax      # imm = 0x3A00
  4013cb: 89 44 24 e4                  	movl	%eax, -28(%rsp)
  4013cf: 8b 44 24 e4                  	movl	-28(%rsp), %eax
  4013d3: 69 c0 29 9f 00 00            	imull	$40745, %eax, %eax      # imm = 0x9F29
  4013d9: 89 44 24 e4                  	movl	%eax, -28(%rsp)
  4013dd: 8b 44 24 ec                  	movl	-20(%rsp), %eax
  4013e1: 69 c0 96 16 00 00            	imull	$5782, %eax, %eax       # imm = 0x1696
  4013e7: 89 44 24 ec                  	movl	%eax, -20(%rsp)
  4013eb: 8b 44 24 d4                  	movl	-44(%rsp), %eax
  4013ef: 69 c0 4d 29 00 00            	imull	$10573, %eax, %eax      # imm = 0x294D
  4013f5: 89 44 24 d4                  	movl	%eax, -44(%rsp)
  4013f9: 8b 44 24 ec                  	movl	-20(%rsp), %eax
  4013fd: 69 c0 7d c8 00 00            	imull	$51325, %eax, %eax      # imm = 0xC87D
  401403: 89 44 24 ec                  	movl	%eax, -20(%rsp)
  401407: 8b 44 24 d4                  	movl	-44(%rsp), %eax
  40140b: 69 c0 7e 90 00 00            	imull	$36990, %eax, %eax      # imm = 0x907E
  401411: 89 44 24 d4                  	movl	%eax, -44(%rsp)
  401415: 8b 44 24 c8                  	movl	-56(%rsp), %eax
  401419: 69 c0 5f c3 00 00            	imull	$50015, %eax, %eax      # imm = 0xC35F
  40141f: 89 44 24 c8                  	movl	%eax, -56(%rsp)
  401423: 8b 44 24 d0                  	movl	-48(%rsp), %eax
  401427: 69 c0 32 43 00 00            	imull	$17202, %eax, %eax      # imm = 0x4332
  40142d: 89 44 24 d0                  	movl	%eax, -48(%rsp)
  401431: 8b 44 24 dc                  	movl	-36(%rsp), %eax
  401435: 69 c0 d9 3f 00 00            	imull	$16345, %eax, %eax      # imm = 0x3FD9
  40143b: 89 44 24 dc                  	movl	%eax, -36(%rsp)
  40143f: 8b 44 24 cc                  	movl	-52(%rsp), %eax
  401443: 69 c0 d7 49 00 00            	imull	$18903, %eax, %eax      # imm = 0x49D7
  401449: 89 44 24 cc                  	movl	%eax, -52(%rsp)
  40144d: 8b 44 24 c8                  	movl	-56(%rsp), %eax
  401451: 69 c0 7a 8c 00 00            	imull	$35962, %eax, %eax      # imm = 0x8C7A
  401457: 89 44 24 c8                  	movl	%eax, -56(%rsp)
  40145b: 8b 44 24 d4                  	movl	-44(%rsp), %eax
  40145f: 69 c0 f8 0e 00 00            	imull	$3832, %eax, %eax       # imm = 0xEF8
  401465: 89 44 24 d4                  	movl	%eax, -44(%rsp)
  401469: 8b 44 24 e0                  	movl	-32(%rsp), %eax
  40146d: 69 c0 2d 12 00 00            	imull	$4653, %eax, %eax       # imm = 0x122D
  401473: 89 44 24 e0                  	movl	%eax, -32(%rsp)
  401477: 8b 44 24 d0                  	movl	-48(%rsp), %eax
  40147b: 69 c0 16 c6 00 00            	imull	$50710, %eax, %eax      # imm = 0xC616
  401481: 89 44 24 d0                  	movl	%eax, -48(%rsp)
  401485: 8b 44 24 e0                  	movl	-32(%rsp), %eax
  401489: 69 c0 41 48 00 00            	imull	$18497, %eax, %eax      # imm = 0x4841
  40148f: 89 44 24 e0                  	movl	%eax, -32(%rsp)
  401493: 8b 44 24 e4                  	movl	-28(%rsp), %eax
  401497: 69 c0 44 92 00 00            	imull	$37444, %eax, %eax      # imm = 0x9244
  40149d: 89 44 24 e4                  	movl	%eax, -28(%rsp)
  4014a1: 8b 44 24 e4                  	movl	-28(%rsp), %eax
  4014a5: 69 c0 19 5f 00 00            	imull	$24345, %eax, %eax      # imm = 0x5F19
  4014ab: 89 44 24 e4                  	movl	%eax, -28(%rsp)
  4014af: 8b 44 24 e4                  	movl	-28(%rsp), %eax
  4014b3: 69 c0 8d 3a 00 00            	imull	$14989, %eax, %eax      # imm = 0x3A8D
  4014b9: 89 44 24 e4                  	movl	%eax, -28(%rsp)
  4014bd: 8b 44 24 e0                  	movl	-32(%rsp), %eax
  4014c1: 69 c0 30 4a 00 00            	imull	$18992, %eax, %eax      # imm = 0x4A30
  4014c7: 89 44 24 e0                  	movl	%eax, -32(%rsp)
  4014cb: 8b 44 24 dc                  	movl	-36(%rsp), %eax
  4014cf: 69 c0 74 f2 00 00            	imull	$62068, %eax, %eax      # imm = 0xF274
  4014d5: 89 44 24 dc                  	movl	%eax, -36(%rsp)
  4014d9: 8b 44 24 d8                  	movl	-40(%rsp), %eax
  4014dd: 69 c0 04 82 00 00            	imull	$33284, %eax, %eax      # imm = 0x8204
  4014e3: 89 44 24 d8                  	movl	%eax, -40(%rsp)
  4014e7: 8b 44 24 dc                  	movl	-36(%rsp), %eax
  4014eb: 69 c0 82 d5 00 00            	imull	$54658, %eax, %eax      # imm = 0xD582
  4014f1: 89 44 24 dc                  	movl	%eax, -36(%rsp)
  4014f5: 8b 44 24 dc                  	movl	-36(%rsp), %eax
  4014f9: 69 c0 cc 01 00 00            	imull	$460, %eax, %eax        # imm = 0x1CC
  4014ff: 89 44 24 dc                  	movl	%eax, -36(%rsp)
  401503: 8b 44 24 e0                  	movl	-32(%rsp), %eax
  401507: 69 c0 77 0d 00 00            	imull	$3447, %eax, %eax       # imm = 0xD77
  40150d: 89 44 24 e0                  	movl	%eax, -32(%rsp)
  401511: 8b 44 24 e0                  	movl	-32(%rsp), %eax
  401515: 69 c0 50 d8 00 00            	imull	$55376, %eax, %eax      # imm = 0xD850
  40151b: 89 44 24 e0                  	movl	%eax, -32(%rsp)
  40151f: 8b 44 24 d4                  	movl	-44(%rsp), %eax
  401523: 69 c0 45 02 00 00            	imull	$581, %eax, %eax        # imm = 0x245
  401529: 89 44 24 d4                  	movl	%eax, -44(%rsp)
  40152d: 8b 44 24 dc                  	movl	-36(%rsp), %eax
  401531: 69 c0 5c b6 00 00            	imull	$46684, %eax, %eax      # imm = 0xB65C
  401537: 89 44 24 dc                  	movl	%eax, -36(%rsp)
  40153b: 8b 44 24 d0                  	movl	-48(%rsp), %eax
  40153f: 69 c0 62 b1 00 00            	imull	$45410, %eax, %eax      # imm = 0xB162
  401545: 89 44 24 d0                  	movl	%eax, -48(%rsp)
  401549: 8b 44 24 cc                  	movl	-52(%rsp), %eax
  40154d: 69 c0 2f b8 00 00            	imull	$47151, %eax, %eax      # imm = 0xB82F
  401553: 89 44 24 cc                  	movl	%eax, -52(%rsp)
  401557: 8b 44 24 e0                  	movl	-32(%rsp), %eax
  40155b: 69 c0 fc 80 00 00            	imull	$33020, %eax, %eax      # imm = 0x80FC
  401561: 89 44 24 e0                  	movl	%eax, -32(%rsp)
  401565: 8b 44 24 e8                  	movl	-24(%rsp), %eax
  401569: 69 c0 65 8e 00 00            	imull	$36453, %eax, %eax      # imm = 0x8E65
  40156f: 89 44 24 e8                  	movl	%eax, -24(%rsp)
  401573: 8b 44 24 c8                  	movl	-56(%rsp), %eax
  401577: 69 c0 b2 82 00 00            	imull	$33458, %eax, %eax      # imm = 0x82B2
  40157d: 89 44 24 c8                  	movl	%eax, -56(%rsp)
  401581: 8b 44 24 d4                  	movl	-44(%rsp), %eax
  401585: 69 c0 ad 44 00 00            	imull	$17581, %eax, %eax      # imm = 0x44AD
  40158b: 89 44 24 d4                  	movl	%eax, -44(%rsp)
  40158f: 8b 44 24 dc                  	movl	-36(%rsp), %eax
  401593: 69 c0 2e 63 00 00            	imull	$25390, %eax, %eax      # imm = 0x632E
  401599: 89 44 24 dc                  	movl	%eax, -36(%rsp)
  40159d: 8b 44 24 c8                  	movl	-56(%rsp), %eax
  4015a1: 69 c0 19 21 00 00            	imull	$8473, %eax, %eax       # imm = 0x2119
  4015a7: 89 44 24 c8                  	movl	%eax, -56(%rsp)
  4015ab: 8b 44 24 e4                  	movl	-28(%rsp), %eax
  4015af: 69 c0 8a a1 00 00            	imull	$41354, %eax, %eax      # imm = 0xA18A
  4015b5: 89 44 24 e4                  	movl	%eax, -28(%rsp)
  4015b9: 8b 44 24 d8                  	movl	-40(%rsp), %eax
  4015bd: 69 c0 95 d8 00 00            	imull	$55445, %eax, %eax      # imm = 0xD895
  4015c3: 89 44 24 d8                  	movl	%eax, -40(%rsp)
  4015c7: 8b 44 24 d4                  	movl	-44(%rsp), %eax
  4015cb: 69 c0 81 e8 00 00            	imull	$59521, %eax, %eax      # imm = 0xE881
  4015d1: 89 44 24 d4                  	movl	%eax, -44(%rsp)
  4015d5: 8b 44 24 d8                  	movl	-40(%rsp), %eax
  4015d9: 69 c0 c1 8f 00 00            	imull	$36801, %eax, %eax      # imm = 0x8FC1
  4015df: 89 44 24 d8                  	movl	%eax, -40(%rsp)
  4015e3: 8b 44 24 d0                  	movl	-48(%rsp), %eax
  4015e7: 69 c0 07 1c 00 00            	imull	$7175, %eax, %eax       # imm = 0x1C07
  4015ed: 89 44 24 d0                  	movl	%eax, -48(%rsp)
  4015f1: 8b 44 24 c8                  	movl	-56(%rsp), %eax
  4015f5: 69 c0 47 4d 00 00            	imull	$19783, %eax, %eax      # imm = 0x4D47
  4015fb: 89 44 24 c8                  	movl	%eax, -56(%rsp)
  4015ff: 8b 44 24 cc                  	movl	-52(%rsp), %eax
  401603: 69 c0 dd cc 00 00            	imull	$52445, %eax, %eax      # imm = 0xCCDD
  401609: 89 44 24 cc                  	movl	%eax, -52(%rsp)
  40160d: 8b 44 24 d4                  	movl	-44(%rsp), %eax
  401611: 69 c0 89 2f 00 00            	imull	$12169, %eax, %eax      # imm = 0x2F89
  401617: 89 44 24 d4                  	movl	%eax, -44(%rsp)
  40161b: 8b 44 24 c8                  	movl	-56(%rsp), %eax
  40161f: 69 c0 2d cc 00 00            	imull	$52269, %eax, %eax      # imm = 0xCC2D
  401625: 89 44 24 c8                  	movl	%eax, -56(%rsp)
  401629: 8b 44 24 cc                  	movl	-52(%rsp), %eax
  40162d: 69 c0 b8 f5 00 00            	imull	$62904, %eax, %eax      # imm = 0xF5B8
  401633: 89 44 24 cc                  	movl	%eax, -52(%rsp)
  401637: 8b 44 24 dc                  	movl	-36(%rsp), %eax
  40163b: 69 c0 29 e8 00 00            	imull	$59433, %eax, %eax      # imm = 0xE829
  401641: 89 44 24 dc                  	movl	%eax, -36(%rsp)
  401645: 8b 44 24 dc                  	movl	-36(%rsp), %eax
  401649: 69 c0 69 60 00 00            	imull	$24681, %eax, %eax      # imm = 0x6069
  40164f: 89 44 24 dc                  	movl	%eax, -36(%rsp)
  401653: 8b 44 24 e8                  	movl	-24(%rsp), %eax
  401657: 69 c0 9c 71 00 00            	imull	$29084, %eax, %eax      # imm = 0x719C
  40165d: 89 44 24 e8                  	movl	%eax, -24(%rsp)
  401661: 8b 44 24 e8                  	movl	-24(%rsp), %eax
  401665: 69 c0 1a 28 00 00            	imull	$10266, %eax, %eax      # imm = 0x281A
  40166b: 89 44 24 e8                  	movl	%eax, -24(%rsp)
  40166f: 8b 44 24 ec                  	movl	-20(%rsp), %eax
  401673: 69 c0 f3 33 00 00            	imull	$13299, %eax, %eax      # imm = 0x33F3
  401679: 89 44 24 ec                  	movl	%eax, -20(%rsp)
  40167d: 8b 44 24 e4                  	movl	-28(%rsp), %eax
  401681: 69 c0 6c 2a 00 00            	imull	$10860, %eax, %eax      # imm = 0x2A6C
  401687: 89 44 24 e4                  	movl	%eax, -28(%rsp)
  40168b: 8b 44 24 e4                  	movl	-28(%rsp), %eax
  40168f: 69 c0 51 ec 00 00            	imull	$60497, %eax, %eax      # imm = 0xEC51
  401695: 89 44 24 e4                  	movl	%eax, -28(%rsp)
  401699: 8b 44 24 e0                  	movl	-32(%rsp), %eax
  40169d: 69 c0 8a 4c 00 00            	imull	$19594, %eax, %eax      # imm = 0x4C8A
  4016a3: 89 44 24 e0                  	movl	%eax, -32(%rsp)
  4016a7: 8b 44 24 d4                  	movl	-44(%rsp), %eax
  4016ab: 69 c0 63 dd 00 00            	imull	$56675, %eax, %eax      # imm = 0xDD63
  4016b1: 89 44 24 d4                  	movl	%eax, -44(%rsp)
  4016b5: 8b 44 24 d0                  	movl	-48(%rsp), %eax
  4016b9: 69 c0 ca ca 00 00            	imull	$51914, %eax, %eax      # imm = 0xCACA
  4016bf: 89 44 24 d0                  	movl	%eax, -48(%rsp)
  4016c3: 8b 44 24 dc                  	movl	-36(%rsp), %eax
  4016c7: 69 c0 5d 44 00 00            	imull	$17501, %eax, %eax      # imm = 0x445D
  4016cd: 89 44 24 dc                  	movl	%eax, -36(%rsp)
  4016d1: 8b 44 24 d8                  	movl	-40(%rsp), %eax
  4016d5: 69 c0 b7 17 00 00            	imull	$6071, %eax, %eax       # imm = 0x17B7
  4016db: 89 44 24 d8                  	movl	%eax, -40(%rsp)
  4016df: 8b 44 24 d0                  	movl	-48(%rsp), %eax
  4016e3: 69 c0 b5 1b 00 00            	imull	$7093, %eax, %eax       # imm = 0x1BB5
  4016e9: 89 44 24 d0                  	movl	%eax, -48(%rsp)
  4016ed: 8b 44 24 d8                  	movl	-40(%rsp), %eax
  4016f1: 69 c0 7a 8f 00 00            	imull	$36730, %eax, %eax      # imm = 0x8F7A
  4016f7: 89 44 24 d8                  	movl	%eax, -40(%rsp)
  4016fb: 8b 44 24 e0                  	movl	-32(%rsp), %eax
  4016ff: 69 c0 f9 2e 00 00            	imull	$12025, %eax, %eax      # imm = 0x2EF9
  401705: 89 44 24 e0                  	movl	%eax, -32(%rsp)
  401709: 8b 44 24 d8                  	movl	-40(%rsp), %eax
  40170d: 69 c0 0c 35 00 00            	imull	$13580, %eax, %eax      # imm = 0x350C
  401713: 89 44 24 d8                  	movl	%eax, -40(%rsp)
  401717: 8b 44 24 cc                  	movl	-52(%rsp), %eax
  40171b: 69 c0 50 09 00 00            	imull	$2384, %eax, %eax       # imm = 0x950
  401721: 89 44 24 cc                  	movl	%eax, -52(%rsp)
  401725: 8b 44 24 d0                  	movl	-48(%rsp), %eax
  401729: 69 c0 fd 81 00 00            	imull	$33277, %eax, %eax      # imm = 0x81FD
  40172f: 89 44 24 d0                  	movl	%eax, -48(%rsp)
  401733: 8b 44 24 cc                  	movl	-52(%rsp), %eax
  401737: 69 c0 8c 3a 00 00            	imull	$14988, %eax, %eax      # imm = 0x3A8C
  40173d: 89 44 24 cc                  	movl	%eax, -52(%rsp)
  401741: 8b 44 24 dc                  	movl	-36(%rsp), %eax
  401745: 69 c0 b6 4f 00 00            	imull	$20406, %eax, %eax      # imm = 0x4FB6
  40174b: 89 44 24 dc                  	movl	%eax, -36(%rsp)
  40174f: 8b 44 24 c8                  	movl	-56(%rsp), %eax
  401753: 69 c0 4a f3 00 00            	imull	$62282, %eax, %eax      # imm = 0xF34A
  401759: 89 44 24 c8                  	movl	%eax, -56(%rsp)
  40175d: 8b 44 24 cc                  	movl	-52(%rsp), %eax
  401761: 69 c0 fd 43 00 00            	imull	$17405, %eax, %eax      # imm = 0x43FD
  401767: 89 44 24 cc                  	movl	%eax, -52(%rsp)
  40176b: 8b 44 24 e4                  	movl	-28(%rsp), %eax
  40176f: 69 c0 24 7d 00 00            	imull	$32036, %eax, %eax      # imm = 0x7D24
  401775: 89 44 24 e4                  	movl	%eax, -28(%rsp)
  401779: 8b 44 24 ec                  	movl	-20(%rsp), %eax
  40177d: 69 c0 6d b4 00 00            	imull	$46189, %eax, %eax      # imm = 0xB46D
  401783: 89 44 24 ec                  	movl	%eax, -20(%rsp)
  401787: ba 00 00 00 00               	movl	$0, %edx
  40178c: b8 00 00 00 00               	movl	$0, %eax
  401791: eb 0b                        	jmp	0x40179e <scramble+0x416>
  401793: 89 d1                        	movl	%edx, %ecx
  401795: 8b 4c 8c c8                  	movl	-56(%rsp,%rcx,4), %ecx
  401799: 01 c8                        	addl	%ecx, %eax
  40179b: 83 c2 01                     	addl	$1, %edx
  40179e: 83 fa 09                     	cmpl	$9, %edx
  4017a1: 76 f0                        	jbe	0x401793 <scramble+0x40b>
  4017a3: f3 c3                        	rep		retq
  4017a5: 90                           	nop
  4017a6: 90                           	nop
  4017a7: 90                           	nop

00000000004017a8 <getbuf>:
  4017a8: 48 83 ec 28                  	subq	$40, %rsp
  4017ac: 48 89 e7                     	movq	%rsp, %rdi
  4017af: e8 ac 03 00 00               	callq	0x401b60 <Gets>
  4017b4: b8 01 00 00 00               	movl	$1, %eax
  4017b9: 48 83 c4 28                  	addq	$40, %rsp
  4017bd: c3                           	retq
  4017be: 90                           	nop
  4017bf: 90                           	nop

00000000004017c0 <touch1>:
  4017c0: 48 83 ec 08                  	subq	$8, %rsp
  4017c4: c7 05 0e 3d 20 00 01 00 00 00	movl	$1, 2112782(%rip)       # 0x6054dc <vlevel>
  4017ce: bf e5 31 40 00               	movl	$4207077, %edi          # imm = 0x4031E5
  4017d3: e8 e8 f4 ff ff               	callq	0x400cc0 <puts@plt>
  4017d8: bf 01 00 00 00               	movl	$1, %edi
  4017dd: e8 cb 05 00 00               	callq	0x401dad <validate>
  4017e2: bf 00 00 00 00               	movl	$0, %edi
  4017e7: e8 54 f6 ff ff               	callq	0x400e40 <exit@plt>

00000000004017ec <touch2>:
  4017ec: 48 83 ec 08                  	subq	$8, %rsp
  4017f0: 89 fa                        	movl	%edi, %edx
  4017f2: c7 05 e0 3c 20 00 02 00 00 00	movl	$2, 2112736(%rip)       # 0x6054dc <vlevel>
  4017fc: 3b 3d e2 3c 20 00            	cmpl	2112738(%rip), %edi     # 0x6054e4 <cookie>
  401802: 75 20                        	jne	0x401824 <touch2+0x38>
  401804: be 08 32 40 00               	movl	$4207112, %esi          # imm = 0x403208
  401809: bf 01 00 00 00               	movl	$1, %edi
  40180e: b8 00 00 00 00               	movl	$0, %eax
  401813: e8 d8 f5 ff ff               	callq	0x400df0 <__printf_chk@plt>
  401818: bf 02 00 00 00               	movl	$2, %edi
  40181d: e8 8b 05 00 00               	callq	0x401dad <validate>
  401822: eb 1e                        	jmp	0x401842 <touch2+0x56>
  401824: be 30 32 40 00               	movl	$4207152, %esi          # imm = 0x403230
  401829: bf 01 00 00 00               	movl	$1, %edi
  40182e: b8 00 00 00 00               	movl	$0, %eax
  401833: e8 b8 f5 ff ff               	callq	0x400df0 <__printf_chk@plt>
  401838: bf 02 00 00 00               	movl	$2, %edi
  40183d: e8 2d 06 00 00               	callq	0x401e6f <fail>
  401842: bf 00 00 00 00               	movl	$0, %edi
  401847: e8 f4 f5 ff ff               	callq	0x400e40 <exit@plt>

000000000040184c <hexmatch>:
  40184c: 41 54                        	pushq	%r12
  40184e: 55                           	pushq	%rbp
  40184f: 53                           	pushq	%rbx
  401850: 48 83 c4 80                  	addq	$-128, %rsp
  401854: 41 89 fc                     	movl	%edi, %r12d
  401857: 48 89 f5                     	movq	%rsi, %rbp
  40185a: 64 48 8b 04 25 28 00 00 00   	movq	%fs:40, %rax
  401863: 48 89 44 24 78               	movq	%rax, 120(%rsp)
  401868: 31 c0                        	xorl	%eax, %eax
  40186a: e8 41 f5 ff ff               	callq	0x400db0 <random@plt>
  40186f: 48 89 c1                     	movq	%rax, %rcx
  401872: 48 ba 0b d7 a3 70 3d 0a d7 a3	movabsq	$-6640827866535438581, %rdx # imm = 0xA3D70A3D70A3D70B
  40187c: 48 f7 ea                     	imulq	%rdx
  40187f: 48 01 ca                     	addq	%rcx, %rdx
  401882: 48 c1 fa 06                  	sarq	$6, %rdx
  401886: 48 89 c8                     	movq	%rcx, %rax
  401889: 48 c1 f8 3f                  	sarq	$63, %rax
  40188d: 48 29 c2                     	subq	%rax, %rdx
  401890: 48 8d 04 92                  	leaq	(%rdx,%rdx,4), %rax
  401894: 48 8d 04 80                  	leaq	(%rax,%rax,4), %rax
  401898: 48 c1 e0 02                  	shlq	$2, %rax
  40189c: 48 29 c1                     	subq	%rax, %rcx
  40189f: 48 8d 1c 0c                  	leaq	(%rsp,%rcx), %rbx
  4018a3: 45 89 e0                     	movl	%r12d, %r8d
  4018a6: b9 02 32 40 00               	movl	$4207106, %ecx          # imm = 0x403202
  4018ab: 48 c7 c2 ff ff ff ff         	movq	$-1, %rdx
  4018b2: be 01 00 00 00               	movl	$1, %esi
  4018b7: 48 89 df                     	movq	%rbx, %rdi
  4018ba: b8 00 00 00 00               	movl	$0, %eax
  4018bf: e8 ac f5 ff ff               	callq	0x400e70 <__sprintf_chk@plt>
  4018c4: ba 09 00 00 00               	movl	$9, %edx
  4018c9: 48 89 de                     	movq	%rbx, %rsi
  4018cc: 48 89 ef                     	movq	%rbp, %rdi
  4018cf: e8 cc f3 ff ff               	callq	0x400ca0 <strncmp@plt>
  4018d4: 85 c0                        	testl	%eax, %eax
  4018d6: 0f 94 c0                     	sete	%al
  4018d9: 0f b6 c0                     	movzbl	%al, %eax
  4018dc: 48 8b 74 24 78               	movq	120(%rsp), %rsi
  4018e1: 64 48 33 34 25 28 00 00 00   	xorq	%fs:40, %rsi
  4018ea: 74 05                        	je	0x4018f1 <hexmatch+0xa5>
  4018ec: e8 ef f3 ff ff               	callq	0x400ce0 <__stack_chk_fail@plt>
  4018f1: 48 83 ec 80                  	subq	$-128, %rsp
  4018f5: 5b                           	popq	%rbx
  4018f6: 5d                           	popq	%rbp
  4018f7: 41 5c                        	popq	%r12
  4018f9: c3                           	retq

00000000004018fa <touch3>:
  4018fa: 53                           	pushq	%rbx
  4018fb: 48 89 fb                     	movq	%rdi, %rbx
  4018fe: c7 05 d4 3b 20 00 03 00 00 00	movl	$3, 2112468(%rip)       # 0x6054dc <vlevel>
  401908: 48 89 fe                     	movq	%rdi, %rsi
  40190b: 8b 3d d3 3b 20 00            	movl	2112467(%rip), %edi     # 0x6054e4 <cookie>
  401911: e8 36 ff ff ff               	callq	0x40184c <hexmatch>
  401916: 85 c0                        	testl	%eax, %eax
  401918: 74 23                        	je	0x40193d <touch3+0x43>
  40191a: 48 89 da                     	movq	%rbx, %rdx
  40191d: be 58 32 40 00               	movl	$4207192, %esi          # imm = 0x403258
  401922: bf 01 00 00 00               	movl	$1, %edi
  401927: b8 00 00 00 00               	movl	$0, %eax
  40192c: e8 bf f4 ff ff               	callq	0x400df0 <__printf_chk@plt>
  401931: bf 03 00 00 00               	movl	$3, %edi
  401936: e8 72 04 00 00               	callq	0x401dad <validate>
  40193b: eb 21                        	jmp	0x40195e <touch3+0x64>
  40193d: 48 89 da                     	movq	%rbx, %rdx
  401940: be 80 32 40 00               	movl	$4207232, %esi          # imm = 0x403280
  401945: bf 01 00 00 00               	movl	$1, %edi
  40194a: b8 00 00 00 00               	movl	$0, %eax
  40194f: e8 9c f4 ff ff               	callq	0x400df0 <__printf_chk@plt>
  401954: bf 03 00 00 00               	movl	$3, %edi
  401959: e8 11 05 00 00               	callq	0x401e6f <fail>
  40195e: bf 00 00 00 00               	movl	$0, %edi
  401963: e8 d8 f4 ff ff               	callq	0x400e40 <exit@plt>

0000000000401968 <test>:
  401968: 48 83 ec 08                  	subq	$8, %rsp
  40196c: b8 00 00 00 00               	movl	$0, %eax
  401971: e8 32 fe ff ff               	callq	0x4017a8 <getbuf>
  401976: 89 c2                        	movl	%eax, %edx
  401978: be a8 32 40 00               	movl	$4207272, %esi          # imm = 0x4032A8
  40197d: bf 01 00 00 00               	movl	$1, %edi
  401982: b8 00 00 00 00               	movl	$0, %eax
  401987: e8 64 f4 ff ff               	callq	0x400df0 <__printf_chk@plt>
  40198c: 48 83 c4 08                  	addq	$8, %rsp
  401990: c3                           	retq
  401991: 90                           	nop
  401992: 90                           	nop
  401993: 90                           	nop

0000000000401994 <start_farm>:
  401994: b8 01 00 00 00               	movl	$1, %eax
  401999: c3                           	retq

000000000040199a <getval_142>:
  40199a: b8 fb 78 90 90               	movl	$2425387259, %eax       # imm = 0x909078FB
  40199f: c3                           	retq

00000000004019a0 <addval_273>:
  4019a0: 8d 87 48 89 c7 c3            	leal	-1010333368(%rdi), %eax
  4019a6: c3                           	retq

00000000004019a7 <addval_219>:
  4019a7: 8d 87 51 73 58 90            	leal	-1873251503(%rdi), %eax
  4019ad: c3                           	retq

00000000004019ae <setval_237>:
  4019ae: c7 07 48 89 c7 c7            	movl	$3351742792, (%rdi)     # imm = 0xC7C78948
  4019b4: c3                           	retq

00000000004019b5 <setval_424>:
  4019b5: c7 07 54 c2 58 92            	movl	$2455290452, (%rdi)     # imm = 0x9258C254
  4019bb: c3                           	retq

00000000004019bc <setval_470>:
  4019bc: c7 07 63 48 8d c7            	movl	$3347925091, (%rdi)     # imm = 0xC78D4863
  4019c2: c3                           	retq

00000000004019c3 <setval_426>:
  4019c3: c7 07 48 89 c7 90            	movl	$2428995912, (%rdi)     # imm = 0x90C78948
  4019c9: c3                           	retq

00000000004019ca <getval_280>:
  4019ca: b8 29 58 90 c3               	movl	$3281016873, %eax       # imm = 0xC3905829
  4019cf: c3                           	retq

00000000004019d0 <mid_farm>:
  4019d0: b8 01 00 00 00               	movl	$1, %eax
  4019d5: c3                           	retq

00000000004019d6 <add_xy>:
  4019d6: 48 8d 04 37                  	leaq	(%rdi,%rsi), %rax
  4019da: c3                           	retq

00000000004019db <getval_481>:
  4019db: b8 5c 89 c2 90               	movl	$2428668252, %eax       # imm = 0x90C2895C
  4019e0: c3                           	retq

00000000004019e1 <setval_296>:
  4019e1: c7 07 99 d1 90 90            	movl	$2425409945, (%rdi)     # imm = 0x9090D199
  4019e7: c3                           	retq

00000000004019e8 <addval_113>:
  4019e8: 8d 87 89 ce 78 c9            	leal	-914829687(%rdi), %eax
  4019ee: c3                           	retq

00000000004019ef <addval_490>:
  4019ef: 8d 87 8d d1 20 db            	leal	-618606195(%rdi), %eax
  4019f5: c3                           	retq

00000000004019f6 <getval_226>:
  4019f6: b8 89 d1 48 c0               	movl	$3225997705, %eax       # imm = 0xC048D189
  4019fb: c3                           	retq

00000000004019fc <setval_384>:
  4019fc: c7 07 81 d1 84 c0            	movl	$3229929857, (%rdi)     # imm = 0xC084D181
  401a02: c3                           	retq

0000000000401a03 <addval_190>:
  401a03: 8d 87 41 48 89 e0            	leal	-527873983(%rdi), %eax
  401a09: c3                           	retq

0000000000401a0a <setval_276>:
  401a0a: c7 07 88 c2 08 c9            	movl	$3372794504, (%rdi)     # imm = 0xC908C288
  401a10: c3                           	retq

0000000000401a11 <addval_436>:
  401a11: 8d 87 89 ce 90 90            	leal	-1869558135(%rdi), %eax
  401a17: c3                           	retq

0000000000401a18 <getval_345>:
  401a18: b8 48 89 e0 c1               	movl	$3252717896, %eax       # imm = 0xC1E08948
  401a1d: c3                           	retq

0000000000401a1e <addval_479>:
  401a1e: 8d 87 89 c2 00 c9            	leal	-922697079(%rdi), %eax
  401a24: c3                           	retq

0000000000401a25 <addval_187>:
  401a25: 8d 87 89 ce 38 c0            	leal	-1070018935(%rdi), %eax
  401a2b: c3                           	retq

0000000000401a2c <setval_248>:
  401a2c: c7 07 81 ce 08 db            	movl	$3674787457, (%rdi)     # imm = 0xDB08CE81
  401a32: c3                           	retq

0000000000401a33 <getval_159>:
  401a33: b8 89 d1 38 c9               	movl	$3375944073, %eax       # imm = 0xC938D189
  401a38: c3                           	retq

0000000000401a39 <addval_110>:
  401a39: 8d 87 c8 89 e0 c3            	leal	-1008694840(%rdi), %eax
  401a3f: c3                           	retq

0000000000401a40 <addval_487>:
  401a40: 8d 87 89 c2 84 c0            	leal	-1065041271(%rdi), %eax
  401a46: c3                           	retq

0000000000401a47 <addval_201>:
  401a47: 8d 87 48 89 e0 c7            	leal	-941586104(%rdi), %eax
  401a4d: c3                           	retq

0000000000401a4e <getval_272>:
  401a4e: b8 99 d1 08 d2               	movl	$3523793305, %eax       # imm = 0xD208D199
  401a53: c3                           	retq

0000000000401a54 <getval_155>:
  401a54: b8 89 c2 c4 c9               	movl	$3385115273, %eax       # imm = 0xC9C4C289
  401a59: c3                           	retq

0000000000401a5a <setval_299>:
  401a5a: c7 07 48 89 e0 91            	movl	$2447411528, (%rdi)     # imm = 0x91E08948
  401a60: c3                           	retq

0000000000401a61 <addval_404>:
  401a61: 8d 87 89 ce 92 c3            	leal	-1013789047(%rdi), %eax
  401a67: c3                           	retq

0000000000401a68 <getval_311>:
  401a68: b8 89 d1 08 db               	movl	$3674788233, %eax       # imm = 0xDB08D189
  401a6d: c3                           	retq

0000000000401a6e <setval_167>:
  401a6e: c7 07 89 d1 91 c3            	movl	$3281113481, (%rdi)     # imm = 0xC391D189
  401a74: c3                           	retq

0000000000401a75 <setval_328>:
  401a75: c7 07 81 c2 38 d2            	movl	$3526935169, (%rdi)     # imm = 0xD238C281
  401a7b: c3                           	retq

0000000000401a7c <setval_450>:
  401a7c: c7 07 09 ce 08 c9            	movl	$3372797449, (%rdi)     # imm = 0xC908CE09
  401a82: c3                           	retq

0000000000401a83 <addval_358>:
  401a83: 8d 87 08 89 e0 90            	leal	-1864333048(%rdi), %eax
  401a89: c3                           	retq

0000000000401a8a <addval_124>:
  401a8a: 8d 87 89 c2 c7 3c            	leal	1019724425(%rdi), %eax
  401a90: c3                           	retq

0000000000401a91 <getval_169>:
  401a91: b8 88 ce 20 c0               	movl	$3223375496, %eax       # imm = 0xC020CE88
  401a96: c3                           	retq

0000000000401a97 <setval_181>:
  401a97: c7 07 48 89 e0 c2            	movl	$3269495112, (%rdi)     # imm = 0xC2E08948
  401a9d: c3                           	retq

0000000000401a9e <addval_184>:
  401a9e: 8d 87 89 c2 60 d2            	leal	-765410679(%rdi), %eax
  401aa4: c3                           	retq

0000000000401aa5 <getval_472>:
  401aa5: b8 8d ce 20 d2               	movl	$3525365389, %eax       # imm = 0xD220CE8D
  401aaa: c3                           	retq

0000000000401aab <setval_350>:
  401aab: c7 07 48 89 e0 90            	movl	$2430634312, (%rdi)     # imm = 0x90E08948
  401ab1: c3                           	retq

0000000000401ab2 <end_farm>:
  401ab2: b8 01 00 00 00               	movl	$1, %eax
  401ab7: c3                           	retq
  401ab8: 90                           	nop
  401ab9: 90                           	nop
  401aba: 90                           	nop
  401abb: 90                           	nop
  401abc: 90                           	nop
  401abd: 90                           	nop
  401abe: 90                           	nop
  401abf: 90                           	nop

0000000000401ac0 <save_char>:
  401ac0: 8b 05 3e 46 20 00            	movl	2115134(%rip), %eax     # 0x606104 <gets_cnt>
  401ac6: 3d ff 03 00 00               	cmpl	$1023, %eax             # imm = 0x3FF
  401acb: 7f 49                        	jg	0x401b16 <save_char+0x56>
  401acd: 8d 14 40                     	leal	(%rax,%rax,2), %edx
  401ad0: 89 f9                        	movl	%edi, %ecx
  401ad2: c1 e9 04                     	shrl	$4, %ecx
  401ad5: 48 63 c9                     	movslq	%ecx, %rcx
  401ad8: 0f b6 b1 d0 35 40 00         	movzbl	4208080(%rcx), %esi
  401adf: 48 63 ca                     	movslq	%edx, %rcx
  401ae2: 40 88 b1 00 55 60 00         	movb	%sil, 6313216(%rcx)
  401ae9: 8d 4a 01                     	leal	1(%rdx), %ecx
  401aec: 83 e7 0f                     	andl	$15, %edi
  401aef: 0f b6 b7 d0 35 40 00         	movzbl	4208080(%rdi), %esi
  401af6: 48 63 c9                     	movslq	%ecx, %rcx
  401af9: 40 88 b1 00 55 60 00         	movb	%sil, 6313216(%rcx)
  401b00: 83 c2 02                     	addl	$2, %edx
  401b03: 48 63 d2                     	movslq	%edx, %rdx
  401b06: c6 82 00 55 60 00 20         	movb	$32, 6313216(%rdx)
  401b0d: 83 c0 01                     	addl	$1, %eax
  401b10: 89 05 ee 45 20 00            	movl	%eax, 2115054(%rip)     # 0x606104 <gets_cnt>
  401b16: f3 c3                        	rep		retq

0000000000401b18 <save_term>:
  401b18: 8b 05 e6 45 20 00            	movl	2115046(%rip), %eax     # 0x606104 <gets_cnt>
  401b1e: 8d 04 40                     	leal	(%rax,%rax,2), %eax
  401b21: 48 98                        	cltq
  401b23: c6 80 00 55 60 00 00         	movb	$0, 6313216(%rax)
  401b2a: c3                           	retq

0000000000401b2b <check_fail>:
  401b2b: 48 83 ec 08                  	subq	$8, %rsp
  401b2f: 0f be 15 d2 45 20 00         	movsbl	2115026(%rip), %edx     # 0x606108 <target_prefix>
  401b36: 41 b8 00 55 60 00            	movl	$6313216, %r8d          # imm = 0x605500
  401b3c: 8b 0d 96 39 20 00            	movl	2111894(%rip), %ecx     # 0x6054d8 <check_level>
  401b42: be cb 32 40 00               	movl	$4207307, %esi          # imm = 0x4032CB
  401b47: bf 01 00 00 00               	movl	$1, %edi
  401b4c: b8 00 00 00 00               	movl	$0, %eax
  401b51: e8 9a f2 ff ff               	callq	0x400df0 <__printf_chk@plt>
  401b56: bf 01 00 00 00               	movl	$1, %edi
  401b5b: e8 e0 f2 ff ff               	callq	0x400e40 <exit@plt>

0000000000401b60 <Gets>:
  401b60: 41 54                        	pushq	%r12
  401b62: 55                           	pushq	%rbp
  401b63: 53                           	pushq	%rbx
  401b64: 49 89 fc                     	movq	%rdi, %r12
  401b67: c7 05 93 45 20 00 00 00 00 00	movl	$0, 2114963(%rip)       # 0x606104 <gets_cnt>
  401b71: 48 89 fb                     	movq	%rdi, %rbx
  401b74: eb 11                        	jmp	0x401b87 <Gets+0x27>
  401b76: 48 8d 6b 01                  	leaq	1(%rbx), %rbp
  401b7a: 88 03                        	movb	%al, (%rbx)
  401b7c: 0f b6 f8                     	movzbl	%al, %edi
  401b7f: e8 3c ff ff ff               	callq	0x401ac0 <save_char>
  401b84: 48 89 eb                     	movq	%rbp, %rbx
  401b87: 48 8b 3d 42 39 20 00         	movq	2111810(%rip), %rdi     # 0x6054d0 <infile>
  401b8e: e8 2d f2 ff ff               	callq	0x400dc0 <_IO_getc@plt>
  401b93: 83 f8 ff                     	cmpl	$-1, %eax
  401b96: 74 05                        	je	0x401b9d <Gets+0x3d>
  401b98: 83 f8 0a                     	cmpl	$10, %eax
  401b9b: 75 d9                        	jne	0x401b76 <Gets+0x16>
  401b9d: c6 03 00                     	movb	$0, (%rbx)
  401ba0: b8 00 00 00 00               	movl	$0, %eax
  401ba5: e8 6e ff ff ff               	callq	0x401b18 <save_term>
  401baa: 4c 89 e0                     	movq	%r12, %rax
  401bad: 5b                           	popq	%rbx
  401bae: 5d                           	popq	%rbp
  401baf: 41 5c                        	popq	%r12
  401bb1: c3                           	retq

0000000000401bb2 <notify_server>:
  401bb2: 53                           	pushq	%rbx
  401bb3: 48 81 ec 30 40 00 00         	subq	$16432, %rsp            # imm = 0x4030
  401bba: 64 48 8b 04 25 28 00 00 00   	movq	%fs:40, %rax
  401bc3: 48 89 84 24 28 40 00 00      	movq	%rax, 16424(%rsp)
  401bcb: 31 c0                        	xorl	%eax, %eax
  401bcd: 83 3d 14 39 20 00 00         	cmpl	$0, 2111764(%rip)       # 0x6054e8 <is_checker>
  401bd4: 0f 85 b2 01 00 00            	jne	0x401d8c <notify_server+0x1da>
  401bda: 8b 05 24 45 20 00            	movl	2114852(%rip), %eax     # 0x606104 <gets_cnt>
  401be0: 83 c0 64                     	addl	$100, %eax
  401be3: 3d 00 20 00 00               	cmpl	$8192, %eax             # imm = 0x2000
  401be8: 7e 1e                        	jle	0x401c08 <notify_server+0x56>
  401bea: be 00 34 40 00               	movl	$4207616, %esi          # imm = 0x403400
  401bef: bf 01 00 00 00               	movl	$1, %edi
  401bf4: b8 00 00 00 00               	movl	$0, %eax
  401bf9: e8 f2 f1 ff ff               	callq	0x400df0 <__printf_chk@plt>
  401bfe: bf 01 00 00 00               	movl	$1, %edi
  401c03: e8 38 f2 ff ff               	callq	0x400e40 <exit@plt>
  401c08: 89 fb                        	movl	%edi, %ebx
  401c0a: 0f be 15 f7 44 20 00         	movsbl	2114807(%rip), %edx     # 0x606108 <target_prefix>
  401c11: 83 3d 70 38 20 00 00         	cmpl	$0, 2111600(%rip)       # 0x605488 <notify>
  401c18: b8 ff ff ff ff               	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
  401c1d: 0f 45 05 bc 38 20 00         	cmovnel	2111676(%rip), %eax     # 0x6054e0 <authkey>
  401c24: 85 ff                        	testl	%edi, %edi
  401c26: b9 e6 32 40 00               	movl	$4207334, %ecx          # imm = 0x4032E6
  401c2b: 41 b9 e1 32 40 00            	movl	$4207329, %r9d          # imm = 0x4032E1
  401c31: 4c 0f 44 c9                  	cmoveq	%rcx, %r9
  401c35: 48 c7 44 24 18 00 55 60 00   	movq	$6313216, 24(%rsp)      # imm = 0x605500
  401c3e: 89 74 24 10                  	movl	%esi, 16(%rsp)
  401c42: 89 54 24 08                  	movl	%edx, 8(%rsp)
  401c46: 89 04 24                     	movl	%eax, (%rsp)
  401c49: 44 8b 05 f8 34 20 00         	movl	2110712(%rip), %r8d     # 0x605148 <target_id>
  401c50: b9 eb 32 40 00               	movl	$4207339, %ecx          # imm = 0x4032EB
  401c55: ba 00 20 00 00               	movl	$8192, %edx             # imm = 0x2000
  401c5a: be 01 00 00 00               	movl	$1, %esi
  401c5f: 48 8d 7c 24 20               	leaq	32(%rsp), %rdi
  401c64: b8 00 00 00 00               	movl	$0, %eax
  401c69: e8 02 f2 ff ff               	callq	0x400e70 <__sprintf_chk@plt>
  401c6e: 83 3d 13 38 20 00 00         	cmpl	$0, 2111507(%rip)       # 0x605488 <notify>
  401c75: 0f 84 83 00 00 00            	je	0x401cfe <notify_server+0x14c>
  401c7b: 85 db                        	testl	%ebx, %ebx
  401c7d: 74 70                        	je	0x401cef <notify_server+0x13d>
  401c7f: 4c 8d 8c 24 20 20 00 00      	leaq	8224(%rsp), %r9
  401c87: 41 b8 00 00 00 00            	movl	$0, %r8d
  401c8d: 48 8d 4c 24 20               	leaq	32(%rsp), %rcx
  401c92: 48 8b 15 b7 34 20 00         	movq	2110647(%rip), %rdx     # 0x605150 <lab>
  401c99: 48 8b 35 b8 34 20 00         	movq	2110648(%rip), %rsi     # 0x605158 <course>
  401ca0: 48 8b 3d 99 34 20 00         	movq	2110617(%rip), %rdi     # 0x605140 <user_id>
  401ca7: e8 8b 10 00 00               	callq	0x402d37 <driver_post>
  401cac: 85 c0                        	testl	%eax, %eax
  401cae: 79 26                        	jns	0x401cd6 <notify_server+0x124>
  401cb0: 48 8d 94 24 20 20 00 00      	leaq	8224(%rsp), %rdx
  401cb8: be 07 33 40 00               	movl	$4207367, %esi          # imm = 0x403307
  401cbd: bf 01 00 00 00               	movl	$1, %edi
  401cc2: b8 00 00 00 00               	movl	$0, %eax
  401cc7: e8 24 f1 ff ff               	callq	0x400df0 <__printf_chk@plt>
  401ccc: bf 01 00 00 00               	movl	$1, %edi
  401cd1: e8 6a f1 ff ff               	callq	0x400e40 <exit@plt>
  401cd6: bf 30 34 40 00               	movl	$4207664, %edi          # imm = 0x403430
  401cdb: e8 e0 ef ff ff               	callq	0x400cc0 <puts@plt>
  401ce0: bf 13 33 40 00               	movl	$4207379, %edi          # imm = 0x403313
  401ce5: e8 d6 ef ff ff               	callq	0x400cc0 <puts@plt>
  401cea: e9 9d 00 00 00               	jmp	0x401d8c <notify_server+0x1da>
  401cef: bf 1d 33 40 00               	movl	$4207389, %edi          # imm = 0x40331D
  401cf4: e8 c7 ef ff ff               	callq	0x400cc0 <puts@plt>
  401cf9: e9 8e 00 00 00               	jmp	0x401d8c <notify_server+0x1da>
  401cfe: 85 db                        	testl	%ebx, %ebx
  401d00: b8 e6 32 40 00               	movl	$4207334, %eax          # imm = 0x4032E6
  401d05: ba e1 32 40 00               	movl	$4207329, %edx          # imm = 0x4032E1
  401d0a: 48 0f 44 d0                  	cmoveq	%rax, %rdx
  401d0e: be 68 34 40 00               	movl	$4207720, %esi          # imm = 0x403468
  401d13: bf 01 00 00 00               	movl	$1, %edi
  401d18: b8 00 00 00 00               	movl	$0, %eax
  401d1d: e8 ce f0 ff ff               	callq	0x400df0 <__printf_chk@plt>
  401d22: 48 8b 15 17 34 20 00         	movq	2110487(%rip), %rdx     # 0x605140 <user_id>
  401d29: be 24 33 40 00               	movl	$4207396, %esi          # imm = 0x403324
  401d2e: bf 01 00 00 00               	movl	$1, %edi
  401d33: b8 00 00 00 00               	movl	$0, %eax
  401d38: e8 b3 f0 ff ff               	callq	0x400df0 <__printf_chk@plt>
  401d3d: 48 8b 15 14 34 20 00         	movq	2110484(%rip), %rdx     # 0x605158 <course>
  401d44: be 31 33 40 00               	movl	$4207409, %esi          # imm = 0x403331
  401d49: bf 01 00 00 00               	movl	$1, %edi
  401d4e: b8 00 00 00 00               	movl	$0, %eax
  401d53: e8 98 f0 ff ff               	callq	0x400df0 <__printf_chk@plt>
  401d58: 48 8b 15 f1 33 20 00         	movq	2110449(%rip), %rdx     # 0x605150 <lab>
  401d5f: be 3d 33 40 00               	movl	$4207421, %esi          # imm = 0x40333D
  401d64: bf 01 00 00 00               	movl	$1, %edi
  401d69: b8 00 00 00 00               	movl	$0, %eax
  401d6e: e8 7d f0 ff ff               	callq	0x400df0 <__printf_chk@plt>
  401d73: 48 8d 54 24 20               	leaq	32(%rsp), %rdx
  401d78: be 46 33 40 00               	movl	$4207430, %esi          # imm = 0x403346
  401d7d: bf 01 00 00 00               	movl	$1, %edi
  401d82: b8 00 00 00 00               	movl	$0, %eax
  401d87: e8 64 f0 ff ff               	callq	0x400df0 <__printf_chk@plt>
  401d8c: 48 8b 84 24 28 40 00 00      	movq	16424(%rsp), %rax
  401d94: 64 48 33 04 25 28 00 00 00   	xorq	%fs:40, %rax
  401d9d: 74 05                        	je	0x401da4 <notify_server+0x1f2>
  401d9f: e8 3c ef ff ff               	callq	0x400ce0 <__stack_chk_fail@plt>
  401da4: 48 81 c4 30 40 00 00         	addq	$16432, %rsp            # imm = 0x4030
  401dab: 5b                           	popq	%rbx
  401dac: c3                           	retq

0000000000401dad <validate>:
  401dad: 53                           	pushq	%rbx
  401dae: 89 fb                        	movl	%edi, %ebx
  401db0: 83 3d 31 37 20 00 00         	cmpl	$0, 2111281(%rip)       # 0x6054e8 <is_checker>
  401db7: 74 6b                        	je	0x401e24 <validate+0x77>
  401db9: 39 3d 1d 37 20 00            	cmpl	%edi, 2111261(%rip)     # 0x6054dc <vlevel>
  401dbf: 74 14                        	je	0x401dd5 <validate+0x28>
  401dc1: bf 52 33 40 00               	movl	$4207442, %edi          # imm = 0x403352
  401dc6: e8 f5 ee ff ff               	callq	0x400cc0 <puts@plt>
  401dcb: b8 00 00 00 00               	movl	$0, %eax
  401dd0: e8 56 fd ff ff               	callq	0x401b2b <check_fail>
  401dd5: 8b 15 fd 36 20 00            	movl	2111229(%rip), %edx     # 0x6054d8 <check_level>
  401ddb: 39 fa                        	cmpl	%edi, %edx
  401ddd: 74 20                        	je	0x401dff <validate+0x52>
  401ddf: 89 f9                        	movl	%edi, %ecx
  401de1: be 90 34 40 00               	movl	$4207760, %esi          # imm = 0x403490
  401de6: bf 01 00 00 00               	movl	$1, %edi
  401deb: b8 00 00 00 00               	movl	$0, %eax
  401df0: e8 fb ef ff ff               	callq	0x400df0 <__printf_chk@plt>
  401df5: b8 00 00 00 00               	movl	$0, %eax
  401dfa: e8 2c fd ff ff               	callq	0x401b2b <check_fail>
  401dff: 0f be 15 02 43 20 00         	movsbl	2114306(%rip), %edx     # 0x606108 <target_prefix>
  401e06: 41 b8 00 55 60 00            	movl	$6313216, %r8d          # imm = 0x605500
  401e0c: 89 f9                        	movl	%edi, %ecx
  401e0e: be 70 33 40 00               	movl	$4207472, %esi          # imm = 0x403370
  401e13: bf 01 00 00 00               	movl	$1, %edi
  401e18: b8 00 00 00 00               	movl	$0, %eax
  401e1d: e8 ce ef ff ff               	callq	0x400df0 <__printf_chk@plt>
  401e22: eb 49                        	jmp	0x401e6d <validate+0xc0>
  401e24: 39 3d b2 36 20 00            	cmpl	%edi, 2111154(%rip)     # 0x6054dc <vlevel>
  401e2a: 74 18                        	je	0x401e44 <validate+0x97>
  401e2c: bf 52 33 40 00               	movl	$4207442, %edi          # imm = 0x403352
  401e31: e8 8a ee ff ff               	callq	0x400cc0 <puts@plt>
  401e36: 89 de                        	movl	%ebx, %esi
  401e38: bf 00 00 00 00               	movl	$0, %edi
  401e3d: e8 70 fd ff ff               	callq	0x401bb2 <notify_server>
  401e42: eb 29                        	jmp	0x401e6d <validate+0xc0>
  401e44: 0f be 0d bd 42 20 00         	movsbl	2114237(%rip), %ecx     # 0x606108 <target_prefix>
  401e4b: 89 fa                        	movl	%edi, %edx
  401e4d: be b8 34 40 00               	movl	$4207800, %esi          # imm = 0x4034B8
  401e52: bf 01 00 00 00               	movl	$1, %edi
  401e57: b8 00 00 00 00               	movl	$0, %eax
  401e5c: e8 8f ef ff ff               	callq	0x400df0 <__printf_chk@plt>
  401e61: 89 de                        	movl	%ebx, %esi
  401e63: bf 01 00 00 00               	movl	$1, %edi
  401e68: e8 45 fd ff ff               	callq	0x401bb2 <notify_server>
  401e6d: 5b                           	popq	%rbx
  401e6e: c3                           	retq

0000000000401e6f <fail>:
  401e6f: 48 83 ec 08                  	subq	$8, %rsp
  401e73: 83 3d 6e 36 20 00 00         	cmpl	$0, 2111086(%rip)       # 0x6054e8 <is_checker>
  401e7a: 74 0a                        	je	0x401e86 <fail+0x17>
  401e7c: b8 00 00 00 00               	movl	$0, %eax
  401e81: e8 a5 fc ff ff               	callq	0x401b2b <check_fail>
  401e86: 89 fe                        	movl	%edi, %esi
  401e88: bf 00 00 00 00               	movl	$0, %edi
  401e8d: e8 20 fd ff ff               	callq	0x401bb2 <notify_server>
  401e92: 48 83 c4 08                  	addq	$8, %rsp
  401e96: c3                           	retq

0000000000401e97 <bushandler>:
  401e97: 48 83 ec 08                  	subq	$8, %rsp
  401e9b: 83 3d 46 36 20 00 00         	cmpl	$0, 2111046(%rip)       # 0x6054e8 <is_checker>
  401ea2: 74 14                        	je	0x401eb8 <bushandler+0x21>
  401ea4: bf 85 33 40 00               	movl	$4207493, %edi          # imm = 0x403385
  401ea9: e8 12 ee ff ff               	callq	0x400cc0 <puts@plt>
  401eae: b8 00 00 00 00               	movl	$0, %eax
  401eb3: e8 73 fc ff ff               	callq	0x401b2b <check_fail>
  401eb8: bf f0 34 40 00               	movl	$4207856, %edi          # imm = 0x4034F0
  401ebd: e8 fe ed ff ff               	callq	0x400cc0 <puts@plt>
  401ec2: bf 8f 33 40 00               	movl	$4207503, %edi          # imm = 0x40338F
  401ec7: e8 f4 ed ff ff               	callq	0x400cc0 <puts@plt>
  401ecc: be 00 00 00 00               	movl	$0, %esi
  401ed1: bf 00 00 00 00               	movl	$0, %edi
  401ed6: e8 d7 fc ff ff               	callq	0x401bb2 <notify_server>
  401edb: bf 01 00 00 00               	movl	$1, %edi
  401ee0: e8 5b ef ff ff               	callq	0x400e40 <exit@plt>

0000000000401ee5 <seghandler>:
  401ee5: 48 83 ec 08                  	subq	$8, %rsp
  401ee9: 83 3d f8 35 20 00 00         	cmpl	$0, 2110968(%rip)       # 0x6054e8 <is_checker>
  401ef0: 74 14                        	je	0x401f06 <seghandler+0x21>
  401ef2: bf a5 33 40 00               	movl	$4207525, %edi          # imm = 0x4033A5
  401ef7: e8 c4 ed ff ff               	callq	0x400cc0 <puts@plt>
  401efc: b8 00 00 00 00               	movl	$0, %eax
  401f01: e8 25 fc ff ff               	callq	0x401b2b <check_fail>
  401f06: bf 10 35 40 00               	movl	$4207888, %edi          # imm = 0x403510
  401f0b: e8 b0 ed ff ff               	callq	0x400cc0 <puts@plt>
  401f10: bf 8f 33 40 00               	movl	$4207503, %edi          # imm = 0x40338F
  401f15: e8 a6 ed ff ff               	callq	0x400cc0 <puts@plt>
  401f1a: be 00 00 00 00               	movl	$0, %esi
  401f1f: bf 00 00 00 00               	movl	$0, %edi
  401f24: e8 89 fc ff ff               	callq	0x401bb2 <notify_server>
  401f29: bf 01 00 00 00               	movl	$1, %edi
  401f2e: e8 0d ef ff ff               	callq	0x400e40 <exit@plt>

0000000000401f33 <illegalhandler>:
  401f33: 48 83 ec 08                  	subq	$8, %rsp
  401f37: 83 3d aa 35 20 00 00         	cmpl	$0, 2110890(%rip)       # 0x6054e8 <is_checker>
  401f3e: 74 14                        	je	0x401f54 <illegalhandler+0x21>
  401f40: bf b8 33 40 00               	movl	$4207544, %edi          # imm = 0x4033B8
  401f45: e8 76 ed ff ff               	callq	0x400cc0 <puts@plt>
  401f4a: b8 00 00 00 00               	movl	$0, %eax
  401f4f: e8 d7 fb ff ff               	callq	0x401b2b <check_fail>
  401f54: bf 38 35 40 00               	movl	$4207928, %edi          # imm = 0x403538
  401f59: e8 62 ed ff ff               	callq	0x400cc0 <puts@plt>
  401f5e: bf 8f 33 40 00               	movl	$4207503, %edi          # imm = 0x40338F
  401f63: e8 58 ed ff ff               	callq	0x400cc0 <puts@plt>
  401f68: be 00 00 00 00               	movl	$0, %esi
  401f6d: bf 00 00 00 00               	movl	$0, %edi
  401f72: e8 3b fc ff ff               	callq	0x401bb2 <notify_server>
  401f77: bf 01 00 00 00               	movl	$1, %edi
  401f7c: e8 bf ee ff ff               	callq	0x400e40 <exit@plt>

0000000000401f81 <sigalrmhandler>:
  401f81: 48 83 ec 08                  	subq	$8, %rsp
  401f85: 83 3d 5c 35 20 00 00         	cmpl	$0, 2110812(%rip)       # 0x6054e8 <is_checker>
  401f8c: 74 14                        	je	0x401fa2 <sigalrmhandler+0x21>
  401f8e: bf cc 33 40 00               	movl	$4207564, %edi          # imm = 0x4033CC
  401f93: e8 28 ed ff ff               	callq	0x400cc0 <puts@plt>
  401f98: b8 00 00 00 00               	movl	$0, %eax
  401f9d: e8 89 fb ff ff               	callq	0x401b2b <check_fail>
  401fa2: ba 05 00 00 00               	movl	$5, %edx
  401fa7: be 68 35 40 00               	movl	$4207976, %esi          # imm = 0x403568
  401fac: bf 01 00 00 00               	movl	$1, %edi
  401fb1: b8 00 00 00 00               	movl	$0, %eax
  401fb6: e8 35 ee ff ff               	callq	0x400df0 <__printf_chk@plt>
  401fbb: be 00 00 00 00               	movl	$0, %esi
  401fc0: bf 00 00 00 00               	movl	$0, %edi
  401fc5: e8 e8 fb ff ff               	callq	0x401bb2 <notify_server>
  401fca: bf 01 00 00 00               	movl	$1, %edi
  401fcf: e8 6c ee ff ff               	callq	0x400e40 <exit@plt>

0000000000401fd4 <launch>:
  401fd4: 55                           	pushq	%rbp
  401fd5: 48 89 e5                     	movq	%rsp, %rbp
  401fd8: 48 83 ec 10                  	subq	$16, %rsp
  401fdc: 48 89 fa                     	movq	%rdi, %rdx
  401fdf: 64 48 8b 04 25 28 00 00 00   	movq	%fs:40, %rax
  401fe8: 48 89 45 f8                  	movq	%rax, -8(%rbp)
  401fec: 31 c0                        	xorl	%eax, %eax
  401fee: 48 8d 47 1e                  	leaq	30(%rdi), %rax
  401ff2: 48 83 e0 f0                  	andq	$-16, %rax
  401ff6: 48 29 c4                     	subq	%rax, %rsp
  401ff9: 48 8d 7c 24 0f               	leaq	15(%rsp), %rdi
  401ffe: 48 83 e7 f0                  	andq	$-16, %rdi
  402002: be f4 00 00 00               	movl	$244, %esi
  402007: e8 f4 ec ff ff               	callq	0x400d00 <memset@plt>
  40200c: 48 8b 05 8d 34 20 00         	movq	2110605(%rip), %rax     # 0x6054a0 <stdin@@GLIBC_2.2.5>
  402013: 48 39 05 b6 34 20 00         	cmpq	%rax, 2110646(%rip)     # 0x6054d0 <infile>
  40201a: 75 14                        	jne	0x402030 <launch+0x5c>
  40201c: be d4 33 40 00               	movl	$4207572, %esi          # imm = 0x4033D4
  402021: bf 01 00 00 00               	movl	$1, %edi
  402026: b8 00 00 00 00               	movl	$0, %eax
  40202b: e8 c0 ed ff ff               	callq	0x400df0 <__printf_chk@plt>
  402030: c7 05 a2 34 20 00 00 00 00 00	movl	$0, 2110626(%rip)       # 0x6054dc <vlevel>
  40203a: b8 00 00 00 00               	movl	$0, %eax
  40203f: e8 24 f9 ff ff               	callq	0x401968 <test>
  402044: 83 3d 9d 34 20 00 00         	cmpl	$0, 2110621(%rip)       # 0x6054e8 <is_checker>
  40204b: 74 14                        	je	0x402061 <launch+0x8d>
  40204d: bf e1 33 40 00               	movl	$4207585, %edi          # imm = 0x4033E1
  402052: e8 69 ec ff ff               	callq	0x400cc0 <puts@plt>
  402057: b8 00 00 00 00               	movl	$0, %eax
  40205c: e8 ca fa ff ff               	callq	0x401b2b <check_fail>
  402061: bf ec 33 40 00               	movl	$4207596, %edi          # imm = 0x4033EC
  402066: e8 55 ec ff ff               	callq	0x400cc0 <puts@plt>
  40206b: 48 8b 45 f8                  	movq	-8(%rbp), %rax
  40206f: 64 48 33 04 25 28 00 00 00   	xorq	%fs:40, %rax
  402078: 74 05                        	je	0x40207f <launch+0xab>
  40207a: e8 61 ec ff ff               	callq	0x400ce0 <__stack_chk_fail@plt>
  40207f: c9                           	leave
  402080: c3                           	retq

0000000000402081 <stable_launch>:
  402081: 53                           	pushq	%rbx
  402082: 48 89 3d 3f 34 20 00         	movq	%rdi, 2110527(%rip)     # 0x6054c8 <global_offset>
  402089: 41 b9 00 00 00 00            	movl	$0, %r9d
  40208f: 41 b8 00 00 00 00            	movl	$0, %r8d
  402095: b9 32 01 00 00               	movl	$306, %ecx              # imm = 0x132
  40209a: ba 07 00 00 00               	movl	$7, %edx
  40209f: be 00 00 10 00               	movl	$1048576, %esi          # imm = 0x100000
  4020a4: bf 00 60 58 55               	movl	$1431855104, %edi       # imm = 0x55586000
  4020a9: e8 42 ec ff ff               	callq	0x400cf0 <mmap@plt>
  4020ae: 48 89 c3                     	movq	%rax, %rbx
  4020b1: 48 3d 00 60 58 55            	cmpq	$1431855104, %rax       # imm = 0x55586000
  4020b7: 74 37                        	je	0x4020f0 <stable_launch+0x6f>
  4020b9: be 00 00 10 00               	movl	$1048576, %esi          # imm = 0x100000
  4020be: 48 89 c7                     	movq	%rax, %rdi
  4020c1: e8 1a ed ff ff               	callq	0x400de0 <munmap@plt>
  4020c6: b9 00 60 58 55               	movl	$1431855104, %ecx       # imm = 0x55586000
  4020cb: ba a0 35 40 00               	movl	$4208032, %edx          # imm = 0x4035A0
  4020d0: be 01 00 00 00               	movl	$1, %esi
  4020d5: 48 8b 3d d4 33 20 00         	movq	2110420(%rip), %rdi     # 0x6054b0 <stderr@@GLIBC_2.2.5>
  4020dc: b8 00 00 00 00               	movl	$0, %eax
  4020e1: e8 7a ed ff ff               	callq	0x400e60 <__fprintf_chk@plt>
  4020e6: bf 01 00 00 00               	movl	$1, %edi
  4020eb: e8 50 ed ff ff               	callq	0x400e40 <exit@plt>
  4020f0: 48 8d 90 f8 ff 0f 00         	leaq	1048568(%rax), %rdx
  4020f7: 48 89 15 12 40 20 00         	movq	%rdx, 2113554(%rip)     # 0x606110 <stack_top>
  4020fe: 48 89 e0                     	movq	%rsp, %rax
  402101: 48 89 d4                     	movq	%rdx, %rsp
  402104: 48 89 c2                     	movq	%rax, %rdx
  402107: 48 89 15 b2 33 20 00         	movq	%rdx, 2110386(%rip)     # 0x6054c0 <global_save_stack>
  40210e: 48 8b 3d b3 33 20 00         	movq	2110387(%rip), %rdi     # 0x6054c8 <global_offset>
  402115: e8 ba fe ff ff               	callq	0x401fd4 <launch>
  40211a: 48 8b 05 9f 33 20 00         	movq	2110367(%rip), %rax     # 0x6054c0 <global_save_stack>
  402121: 48 89 c4                     	movq	%rax, %rsp
  402124: be 00 00 10 00               	movl	$1048576, %esi          # imm = 0x100000
  402129: 48 89 df                     	movq	%rbx, %rdi
  40212c: e8 af ec ff ff               	callq	0x400de0 <munmap@plt>
  402131: 5b                           	popq	%rbx
  402132: c3                           	retq
  402133: 90                           	nop
  402134: 90                           	nop
  402135: 90                           	nop
  402136: 90                           	nop
  402137: 90                           	nop
  402138: 90                           	nop
  402139: 90                           	nop
  40213a: 90                           	nop
  40213b: 90                           	nop
  40213c: 90                           	nop
  40213d: 90                           	nop
  40213e: 90                           	nop
  40213f: 90                           	nop

0000000000402140 <rio_readinitb>:
  402140: 89 37                        	movl	%esi, (%rdi)
  402142: c7 47 04 00 00 00 00         	movl	$0, 4(%rdi)
  402149: 48 8d 47 10                  	leaq	16(%rdi), %rax
  40214d: 48 89 47 08                  	movq	%rax, 8(%rdi)
  402151: c3                           	retq

0000000000402152 <sigalrm_handler>:
  402152: 48 83 ec 08                  	subq	$8, %rsp
  402156: b9 00 00 00 00               	movl	$0, %ecx
  40215b: ba e0 35 40 00               	movl	$4208096, %edx          # imm = 0x4035E0
  402160: be 01 00 00 00               	movl	$1, %esi
  402165: 48 8b 3d 44 33 20 00         	movq	2110276(%rip), %rdi     # 0x6054b0 <stderr@@GLIBC_2.2.5>
  40216c: b8 00 00 00 00               	movl	$0, %eax
  402171: e8 ea ec ff ff               	callq	0x400e60 <__fprintf_chk@plt>
  402176: bf 01 00 00 00               	movl	$1, %edi
  40217b: e8 c0 ec ff ff               	callq	0x400e40 <exit@plt>

0000000000402180 <rio_writen>:
  402180: 41 55                        	pushq	%r13
  402182: 41 54                        	pushq	%r12
  402184: 55                           	pushq	%rbp
  402185: 53                           	pushq	%rbx
  402186: 48 83 ec 08                  	subq	$8, %rsp
  40218a: 41 89 fc                     	movl	%edi, %r12d
  40218d: 48 89 f5                     	movq	%rsi, %rbp
  402190: 49 89 d5                     	movq	%rdx, %r13
  402193: 48 89 d3                     	movq	%rdx, %rbx
  402196: eb 28                        	jmp	0x4021c0 <rio_writen+0x40>
  402198: 48 89 da                     	movq	%rbx, %rdx
  40219b: 48 89 ee                     	movq	%rbp, %rsi
  40219e: 44 89 e7                     	movl	%r12d, %edi
  4021a1: e8 2a eb ff ff               	callq	0x400cd0 <write@plt>
  4021a6: 48 85 c0                     	testq	%rax, %rax
  4021a9: 7f 0f                        	jg	0x4021ba <rio_writen+0x3a>
  4021ab: e8 d0 ea ff ff               	callq	0x400c80 <__errno_location@plt>
  4021b0: 83 38 04                     	cmpl	$4, (%rax)
  4021b3: 75 15                        	jne	0x4021ca <rio_writen+0x4a>
  4021b5: b8 00 00 00 00               	movl	$0, %eax
  4021ba: 48 29 c3                     	subq	%rax, %rbx
  4021bd: 48 01 c5                     	addq	%rax, %rbp
  4021c0: 48 85 db                     	testq	%rbx, %rbx
  4021c3: 75 d3                        	jne	0x402198 <rio_writen+0x18>
  4021c5: 4c 89 e8                     	movq	%r13, %rax
  4021c8: eb 07                        	jmp	0x4021d1 <rio_writen+0x51>
  4021ca: 48 c7 c0 ff ff ff ff         	movq	$-1, %rax
  4021d1: 48 83 c4 08                  	addq	$8, %rsp
  4021d5: 5b                           	popq	%rbx
  4021d6: 5d                           	popq	%rbp
  4021d7: 41 5c                        	popq	%r12
  4021d9: 41 5d                        	popq	%r13
  4021db: c3                           	retq

00000000004021dc <rio_read>:
  4021dc: 41 55                        	pushq	%r13
  4021de: 41 54                        	pushq	%r12
  4021e0: 55                           	pushq	%rbp
  4021e1: 53                           	pushq	%rbx
  4021e2: 48 83 ec 08                  	subq	$8, %rsp
  4021e6: 48 89 fb                     	movq	%rdi, %rbx
  4021e9: 49 89 f5                     	movq	%rsi, %r13
  4021ec: 49 89 d4                     	movq	%rdx, %r12
  4021ef: 48 8d 6f 10                  	leaq	16(%rdi), %rbp
  4021f3: eb 2a                        	jmp	0x40221f <rio_read+0x43>
  4021f5: 8b 3b                        	movl	(%rbx), %edi
  4021f7: ba 00 20 00 00               	movl	$8192, %edx             # imm = 0x2000
  4021fc: 48 89 ee                     	movq	%rbp, %rsi
  4021ff: e8 2c eb ff ff               	callq	0x400d30 <read@plt>
  402204: 89 43 04                     	movl	%eax, 4(%rbx)
  402207: 85 c0                        	testl	%eax, %eax
  402209: 79 0c                        	jns	0x402217 <rio_read+0x3b>
  40220b: e8 70 ea ff ff               	callq	0x400c80 <__errno_location@plt>
  402210: 83 38 04                     	cmpl	$4, (%rax)
  402213: 74 0a                        	je	0x40221f <rio_read+0x43>
  402215: eb 37                        	jmp	0x40224e <rio_read+0x72>
  402217: 85 c0                        	testl	%eax, %eax
  402219: 74 3c                        	je	0x402257 <rio_read+0x7b>
  40221b: 48 89 6b 08                  	movq	%rbp, 8(%rbx)
  40221f: 8b 43 04                     	movl	4(%rbx), %eax
  402222: 85 c0                        	testl	%eax, %eax
  402224: 7e cf                        	jle	0x4021f5 <rio_read+0x19>
  402226: 89 c2                        	movl	%eax, %edx
  402228: 4c 39 e2                     	cmpq	%r12, %rdx
  40222b: 44 0f 42 e0                  	cmovbl	%eax, %r12d
  40222f: 49 63 ec                     	movslq	%r12d, %rbp
  402232: 48 8b 73 08                  	movq	8(%rbx), %rsi
  402236: 48 89 ea                     	movq	%rbp, %rdx
  402239: 4c 89 ef                     	movq	%r13, %rdi
  40223c: e8 4f eb ff ff               	callq	0x400d90 <memcpy@plt>
  402241: 48 01 6b 08                  	addq	%rbp, 8(%rbx)
  402245: 44 29 63 04                  	subl	%r12d, 4(%rbx)
  402249: 48 89 e8                     	movq	%rbp, %rax
  40224c: eb 0e                        	jmp	0x40225c <rio_read+0x80>
  40224e: 48 c7 c0 ff ff ff ff         	movq	$-1, %rax
  402255: eb 05                        	jmp	0x40225c <rio_read+0x80>
  402257: b8 00 00 00 00               	movl	$0, %eax
  40225c: 48 83 c4 08                  	addq	$8, %rsp
  402260: 5b                           	popq	%rbx
  402261: 5d                           	popq	%rbp
  402262: 41 5c                        	popq	%r12
  402264: 41 5d                        	popq	%r13
  402266: c3                           	retq

0000000000402267 <rio_readlineb>:
  402267: 41 55                        	pushq	%r13
  402269: 41 54                        	pushq	%r12
  40226b: 55                           	pushq	%rbp
  40226c: 53                           	pushq	%rbx
  40226d: 48 83 ec 18                  	subq	$24, %rsp
  402271: 49 89 fd                     	movq	%rdi, %r13
  402274: 48 89 f5                     	movq	%rsi, %rbp
  402277: 49 89 d4                     	movq	%rdx, %r12
  40227a: bb 01 00 00 00               	movl	$1, %ebx
  40227f: eb 3c                        	jmp	0x4022bd <rio_readlineb+0x56>
  402281: ba 01 00 00 00               	movl	$1, %edx
  402286: 48 8d 74 24 0f               	leaq	15(%rsp), %rsi
  40228b: 4c 89 ef                     	movq	%r13, %rdi
  40228e: e8 49 ff ff ff               	callq	0x4021dc <rio_read>
  402293: 83 f8 01                     	cmpl	$1, %eax
  402296: 75 12                        	jne	0x4022aa <rio_readlineb+0x43>
  402298: 48 8d 55 01                  	leaq	1(%rbp), %rdx
  40229c: 0f b6 44 24 0f               	movzbl	15(%rsp), %eax
  4022a1: 88 45 00                     	movb	%al, (%rbp)
  4022a4: 3c 0a                        	cmpb	$10, %al
  4022a6: 75 0e                        	jne	0x4022b6 <rio_readlineb+0x4f>
  4022a8: eb 1a                        	jmp	0x4022c4 <rio_readlineb+0x5d>
  4022aa: 85 c0                        	testl	%eax, %eax
  4022ac: 75 22                        	jne	0x4022d0 <rio_readlineb+0x69>
  4022ae: 48 83 fb 01                  	cmpq	$1, %rbx
  4022b2: 75 13                        	jne	0x4022c7 <rio_readlineb+0x60>
  4022b4: eb 23                        	jmp	0x4022d9 <rio_readlineb+0x72>
  4022b6: 48 83 c3 01                  	addq	$1, %rbx
  4022ba: 48 89 d5                     	movq	%rdx, %rbp
  4022bd: 4c 39 e3                     	cmpq	%r12, %rbx
  4022c0: 72 bf                        	jb	0x402281 <rio_readlineb+0x1a>
  4022c2: eb 03                        	jmp	0x4022c7 <rio_readlineb+0x60>
  4022c4: 48 89 d5                     	movq	%rdx, %rbp
  4022c7: c6 45 00 00                  	movb	$0, (%rbp)
  4022cb: 48 89 d8                     	movq	%rbx, %rax
  4022ce: eb 0e                        	jmp	0x4022de <rio_readlineb+0x77>
  4022d0: 48 c7 c0 ff ff ff ff         	movq	$-1, %rax
  4022d7: eb 05                        	jmp	0x4022de <rio_readlineb+0x77>
  4022d9: b8 00 00 00 00               	movl	$0, %eax
  4022de: 48 83 c4 18                  	addq	$24, %rsp
  4022e2: 5b                           	popq	%rbx
  4022e3: 5d                           	popq	%rbp
  4022e4: 41 5c                        	popq	%r12
  4022e6: 41 5d                        	popq	%r13
  4022e8: c3                           	retq

00000000004022e9 <urlencode>:
  4022e9: 41 54                        	pushq	%r12
  4022eb: 55                           	pushq	%rbp
  4022ec: 53                           	pushq	%rbx
  4022ed: 48 83 ec 10                  	subq	$16, %rsp
  4022f1: 48 89 fb                     	movq	%rdi, %rbx
  4022f4: 48 89 f5                     	movq	%rsi, %rbp
  4022f7: 64 48 8b 04 25 28 00 00 00   	movq	%fs:40, %rax
  402300: 48 89 44 24 08               	movq	%rax, 8(%rsp)
  402305: 31 c0                        	xorl	%eax, %eax
  402307: 48 c7 c1 ff ff ff ff         	movq	$-1, %rcx
  40230e: f2 ae                        	repne		scasb	%es:(%rdi), %al
  402310: 48 f7 d1                     	notq	%rcx
  402313: 8d 41 ff                     	leal	-1(%rcx), %eax
  402316: e9 aa 00 00 00               	jmp	0x4023c5 <urlencode+0xdc>
  40231b: 44 0f b6 03                  	movzbl	(%rbx), %r8d
  40231f: 41 80 f8 2a                  	cmpb	$42, %r8b
  402323: 0f 94 c2                     	sete	%dl
  402326: 41 80 f8 2d                  	cmpb	$45, %r8b
  40232a: 0f 94 c0                     	sete	%al
  40232d: 08 c2                        	orb	%al, %dl
  40232f: 75 24                        	jne	0x402355 <urlencode+0x6c>
  402331: 41 80 f8 2e                  	cmpb	$46, %r8b
  402335: 74 1e                        	je	0x402355 <urlencode+0x6c>
  402337: 41 80 f8 5f                  	cmpb	$95, %r8b
  40233b: 74 18                        	je	0x402355 <urlencode+0x6c>
  40233d: 41 8d 40 d0                  	leal	-48(%r8), %eax
  402341: 3c 09                        	cmpb	$9, %al
  402343: 76 10                        	jbe	0x402355 <urlencode+0x6c>
  402345: 41 8d 40 bf                  	leal	-65(%r8), %eax
  402349: 3c 19                        	cmpb	$25, %al
  40234b: 76 08                        	jbe	0x402355 <urlencode+0x6c>
  40234d: 41 8d 40 9f                  	leal	-97(%r8), %eax
  402351: 3c 19                        	cmpb	$25, %al
  402353: 77 0a                        	ja	0x40235f <urlencode+0x76>
  402355: 44 88 45 00                  	movb	%r8b, (%rbp)
  402359: 48 8d 6d 01                  	leaq	1(%rbp), %rbp
  40235d: eb 5f                        	jmp	0x4023be <urlencode+0xd5>
  40235f: 41 80 f8 20                  	cmpb	$32, %r8b
  402363: 75 0a                        	jne	0x40236f <urlencode+0x86>
  402365: c6 45 00 2b                  	movb	$43, (%rbp)
  402369: 48 8d 6d 01                  	leaq	1(%rbp), %rbp
  40236d: eb 4f                        	jmp	0x4023be <urlencode+0xd5>
  40236f: 41 8d 40 e0                  	leal	-32(%r8), %eax
  402373: 3c 5f                        	cmpb	$95, %al
  402375: 0f 96 c2                     	setbe	%dl
  402378: 41 80 f8 09                  	cmpb	$9, %r8b
  40237c: 0f 94 c0                     	sete	%al
  40237f: 08 c2                        	orb	%al, %dl
  402381: 74 50                        	je	0x4023d3 <urlencode+0xea>
  402383: 45 0f b6 c0                  	movzbl	%r8b, %r8d
  402387: b9 78 36 40 00               	movl	$4208248, %ecx          # imm = 0x403678
  40238c: ba 08 00 00 00               	movl	$8, %edx
  402391: be 01 00 00 00               	movl	$1, %esi
  402396: 48 89 e7                     	movq	%rsp, %rdi
  402399: b8 00 00 00 00               	movl	$0, %eax
  40239e: e8 cd ea ff ff               	callq	0x400e70 <__sprintf_chk@plt>
  4023a3: 0f b6 04 24                  	movzbl	(%rsp), %eax
  4023a7: 88 45 00                     	movb	%al, (%rbp)
  4023aa: 0f b6 44 24 01               	movzbl	1(%rsp), %eax
  4023af: 88 45 01                     	movb	%al, 1(%rbp)
  4023b2: 0f b6 44 24 02               	movzbl	2(%rsp), %eax
  4023b7: 88 45 02                     	movb	%al, 2(%rbp)
  4023ba: 48 8d 6d 03                  	leaq	3(%rbp), %rbp
  4023be: 48 83 c3 01                  	addq	$1, %rbx
  4023c2: 44 89 e0                     	movl	%r12d, %eax
  4023c5: 44 8d 60 ff                  	leal	-1(%rax), %r12d
  4023c9: 85 c0                        	testl	%eax, %eax
  4023cb: 0f 85 4a ff ff ff            	jne	0x40231b <urlencode+0x32>
  4023d1: eb 05                        	jmp	0x4023d8 <urlencode+0xef>
  4023d3: b8 ff ff ff ff               	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
  4023d8: 48 8b 74 24 08               	movq	8(%rsp), %rsi
  4023dd: 64 48 33 34 25 28 00 00 00   	xorq	%fs:40, %rsi
  4023e6: 74 05                        	je	0x4023ed <urlencode+0x104>
  4023e8: e8 f3 e8 ff ff               	callq	0x400ce0 <__stack_chk_fail@plt>
  4023ed: 48 83 c4 10                  	addq	$16, %rsp
  4023f1: 5b                           	popq	%rbx
  4023f2: 5d                           	popq	%rbp
  4023f3: 41 5c                        	popq	%r12
  4023f5: c3                           	retq

00000000004023f6 <submitr>:
  4023f6: 41 57                        	pushq	%r15
  4023f8: 41 56                        	pushq	%r14
  4023fa: 41 55                        	pushq	%r13
  4023fc: 41 54                        	pushq	%r12
  4023fe: 55                           	pushq	%rbp
  4023ff: 53                           	pushq	%rbx
  402400: 48 81 ec 68 a0 00 00         	subq	$41064, %rsp            # imm = 0xA068
  402407: 49 89 fc                     	movq	%rdi, %r12
  40240a: 89 74 24 14                  	movl	%esi, 20(%rsp)
  40240e: 49 89 d7                     	movq	%rdx, %r15
  402411: 49 89 ce                     	movq	%rcx, %r14
  402414: 4c 89 44 24 18               	movq	%r8, 24(%rsp)
  402419: 4d 89 cd                     	movq	%r9, %r13
  40241c: 48 8b 9c 24 a0 a0 00 00      	movq	41120(%rsp), %rbx
  402424: 64 48 8b 04 25 28 00 00 00   	movq	%fs:40, %rax
  40242d: 48 89 84 24 58 a0 00 00      	movq	%rax, 41048(%rsp)
  402435: 31 c0                        	xorl	%eax, %eax
  402437: c7 44 24 2c 00 00 00 00      	movl	$0, 44(%rsp)
  40243f: ba 00 00 00 00               	movl	$0, %edx
  402444: be 01 00 00 00               	movl	$1, %esi
  402449: bf 02 00 00 00               	movl	$2, %edi
  40244e: e8 2d ea ff ff               	callq	0x400e80 <socket@plt>
  402453: 89 c5                        	movl	%eax, %ebp
  402455: 85 c0                        	testl	%eax, %eax
  402457: 79 4e                        	jns	0x4024a7 <submitr+0xb1>
  402459: 48 b8 45 72 72 6f 72 3a 20 43	movabsq	$4836930262966366789, %rax # imm = 0x43203A726F727245
  402463: 48 89 03                     	movq	%rax, (%rbx)
  402466: 48 b8 6c 69 65 6e 74 20 75 6e	movabsq	$7959303600887654764, %rax # imm = 0x6E7520746E65696C
  402470: 48 89 43 08                  	movq	%rax, 8(%rbx)
  402474: 48 b8 61 62 6c 65 20 74 6f 20	movabsq	$2337214414117954145, %rax # imm = 0x206F7420656C6261
  40247e: 48 89 43 10                  	movq	%rax, 16(%rbx)
  402482: 48 b8 63 72 65 61 74 65 20 73	movabsq	$8295742064141103715, %rax # imm = 0x7320657461657263
  40248c: 48 89 43 18                  	movq	%rax, 24(%rbx)
  402490: c7 43 20 6f 63 6b 65         	movl	$1701536623, 32(%rbx)   # imm = 0x656B636F
  402497: 66 c7 43 24 74 00            	movw	$116, 36(%rbx)
  40249d: b8 ff ff ff ff               	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
  4024a2: e9 4a 06 00 00               	jmp	0x402af1 <submitr+0x6fb>
  4024a7: 4c 89 e7                     	movq	%r12, %rdi
  4024aa: e8 b1 e8 ff ff               	callq	0x400d60 <gethostbyname@plt>
  4024af: 48 85 c0                     	testq	%rax, %rax
  4024b2: 75 67                        	jne	0x40251b <submitr+0x125>
  4024b4: 48 b8 45 72 72 6f 72 3a 20 44	movabsq	$4908987857004294725, %rax # imm = 0x44203A726F727245
  4024be: 48 89 03                     	movq	%rax, (%rbx)
  4024c1: 48 b8 4e 53 20 69 73 20 75 6e	movabsq	$7959303596504273742, %rax # imm = 0x6E7520736920534E
  4024cb: 48 89 43 08                  	movq	%rax, 8(%rbx)
  4024cf: 48 b8 61 62 6c 65 20 74 6f 20	movabsq	$2337214414117954145, %rax # imm = 0x206F7420656C6261
  4024d9: 48 89 43 10                  	movq	%rax, 16(%rbx)
  4024dd: 48 b8 72 65 73 6f 6c 76 65 20	movabsq	$2334402189959849330, %rax # imm = 0x2065766C6F736572
  4024e7: 48 89 43 18                  	movq	%rax, 24(%rbx)
  4024eb: 48 b8 73 65 72 76 65 72 20 61	movabsq	$6998719601038222707, %rax # imm = 0x6120726576726573
  4024f5: 48 89 43 20                  	movq	%rax, 32(%rbx)
  4024f9: c7 43 28 64 64 72 65         	movl	$1701995620, 40(%rbx)   # imm = 0x65726464
  402500: 66 c7 43 2c 73 73            	movw	$29555, 44(%rbx)        # imm = 0x7373
  402506: c6 43 2e 00                  	movb	$0, 46(%rbx)
  40250a: 89 ef                        	movl	%ebp, %edi
  40250c: e8 0f e8 ff ff               	callq	0x400d20 <close@plt>
  402511: b8 ff ff ff ff               	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
  402516: e9 d6 05 00 00               	jmp	0x402af1 <submitr+0x6fb>
  40251b: 48 c7 44 24 30 00 00 00 00   	movq	$0, 48(%rsp)
  402524: 48 c7 44 24 38 00 00 00 00   	movq	$0, 56(%rsp)
  40252d: 66 c7 44 24 30 02 00         	movw	$2, 48(%rsp)
  402534: 48 63 50 14                  	movslq	20(%rax), %rdx
  402538: 48 8b 40 18                  	movq	24(%rax), %rax
  40253c: 48 8b 30                     	movq	(%rax), %rsi
  40253f: b9 0c 00 00 00               	movl	$12, %ecx
  402544: 48 8d 7c 24 34               	leaq	52(%rsp), %rdi
  402549: e8 22 e8 ff ff               	callq	0x400d70 <__memmove_chk@plt>
  40254e: 0f b7 44 24 14               	movzwl	20(%rsp), %eax
  402553: 66 c1 c8 08                  	rorw	$8, %ax
  402557: 66 89 44 24 32               	movw	%ax, 50(%rsp)
  40255c: ba 10 00 00 00               	movl	$16, %edx
  402561: 48 8d 74 24 30               	leaq	48(%rsp), %rsi
  402566: 89 ef                        	movl	%ebp, %edi
  402568: e8 e3 e8 ff ff               	callq	0x400e50 <connect@plt>
  40256d: 85 c0                        	testl	%eax, %eax
  40256f: 79 59                        	jns	0x4025ca <submitr+0x1d4>
  402571: 48 b8 45 72 72 6f 72 3a 20 55	movabsq	$6133966955649069637, %rax # imm = 0x55203A726F727245
  40257b: 48 89 03                     	movq	%rax, (%rbx)
  40257e: 48 b8 6e 61 62 6c 65 20 74 6f	movabsq	$8031079655490609518, %rax # imm = 0x6F7420656C62616E
  402588: 48 89 43 08                  	movq	%rax, 8(%rbx)
  40258c: 48 b8 20 63 6f 6e 6e 65 63 74	movabsq	$8386658456067597088, %rax # imm = 0x7463656E6E6F6320
  402596: 48 89 43 10                  	movq	%rax, 16(%rbx)
  40259a: 48 b8 20 74 6f 20 74 68 65 20	movabsq	$2334386829831140384, %rax # imm = 0x20656874206F7420
  4025a4: 48 89 43 18                  	movq	%rax, 24(%rbx)
  4025a8: c7 43 20 73 65 72 76         	movl	$1987208563, 32(%rbx)   # imm = 0x76726573
  4025af: 66 c7 43 24 65 72            	movw	$29285, 36(%rbx)        # imm = 0x7265
  4025b5: c6 43 26 00                  	movb	$0, 38(%rbx)
  4025b9: 89 ef                        	movl	%ebp, %edi
  4025bb: e8 60 e7 ff ff               	callq	0x400d20 <close@plt>
  4025c0: b8 ff ff ff ff               	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
  4025c5: e9 27 05 00 00               	jmp	0x402af1 <submitr+0x6fb>
  4025ca: 48 c7 c2 ff ff ff ff         	movq	$-1, %rdx
  4025d1: 4c 89 ef                     	movq	%r13, %rdi
  4025d4: b8 00 00 00 00               	movl	$0, %eax
  4025d9: 48 89 d1                     	movq	%rdx, %rcx
  4025dc: f2 ae                        	repne		scasb	%es:(%rdi), %al
  4025de: 48 f7 d1                     	notq	%rcx
  4025e1: 48 89 ce                     	movq	%rcx, %rsi
  4025e4: 4c 89 ff                     	movq	%r15, %rdi
  4025e7: 48 89 d1                     	movq	%rdx, %rcx
  4025ea: f2 ae                        	repne		scasb	%es:(%rdi), %al
  4025ec: 48 f7 d1                     	notq	%rcx
  4025ef: 49 89 c8                     	movq	%rcx, %r8
  4025f2: 4c 89 f7                     	movq	%r14, %rdi
  4025f5: 48 89 d1                     	movq	%rdx, %rcx
  4025f8: f2 ae                        	repne		scasb	%es:(%rdi), %al
  4025fa: 49 29 c8                     	subq	%rcx, %r8
  4025fd: 48 8b 7c 24 18               	movq	24(%rsp), %rdi
  402602: 48 89 d1                     	movq	%rdx, %rcx
  402605: f2 ae                        	repne		scasb	%es:(%rdi), %al
  402607: 49 29 c8                     	subq	%rcx, %r8
  40260a: 48 8d 44 76 fd               	leaq	-3(%rsi,%rsi,2), %rax
  40260f: 49 8d 44 00 7b               	leaq	123(%r8,%rax), %rax
  402614: 48 3d 00 20 00 00            	cmpq	$8192, %rax             # imm = 0x2000
  40261a: 76 72                        	jbe	0x40268e <submitr+0x298>
  40261c: 48 b8 45 72 72 6f 72 3a 20 52	movabsq	$5917794173535285829, %rax # imm = 0x52203A726F727245
  402626: 48 89 03                     	movq	%rax, (%rbx)
  402629: 48 b8 65 73 75 6c 74 20 73 74	movabsq	$8391086215129297765, %rax # imm = 0x747320746C757365
  402633: 48 89 43 08                  	movq	%rax, 8(%rbx)
  402637: 48 b8 72 69 6e 67 20 74 6f 6f	movabsq	$8029764343147948402, %rax # imm = 0x6F6F7420676E6972
  402641: 48 89 43 10                  	movq	%rax, 16(%rbx)
  402645: 48 b8 20 6c 61 72 67 65 2e 20	movabsq	$2318902353117408288, %rax # imm = 0x202E656772616C20
  40264f: 48 89 43 18                  	movq	%rax, 24(%rbx)
  402653: 48 b8 49 6e 63 72 65 61 73 65	movabsq	$7310293708491157065, %rax # imm = 0x6573616572636E49
  40265d: 48 89 43 20                  	movq	%rax, 32(%rbx)
  402661: 48 b8 20 53 55 42 4d 49 54 52	movabsq	$5932447205327983392, %rax # imm = 0x5254494D42555320
  40266b: 48 89 43 28                  	movq	%rax, 40(%rbx)
  40266f: 48 b8 5f 4d 41 58 42 55 46 00	movabsq	$19796991806623071, %rax # imm = 0x46554258414D5F
  402679: 48 89 43 30                  	movq	%rax, 48(%rbx)
  40267d: 89 ef                        	movl	%ebp, %edi
  40267f: e8 9c e6 ff ff               	callq	0x400d20 <close@plt>
  402684: b8 ff ff ff ff               	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
  402689: e9 63 04 00 00               	jmp	0x402af1 <submitr+0x6fb>
  40268e: 48 8d b4 24 40 20 00 00      	leaq	8256(%rsp), %rsi
  402696: b9 00 04 00 00               	movl	$1024, %ecx             # imm = 0x400
  40269b: b8 00 00 00 00               	movl	$0, %eax
  4026a0: 48 89 f7                     	movq	%rsi, %rdi
  4026a3: f3 48 ab                     	rep		stosq	%rax, %es:(%rdi)
  4026a6: 4c 89 ef                     	movq	%r13, %rdi
  4026a9: e8 3b fc ff ff               	callq	0x4022e9 <urlencode>
  4026ae: 85 c0                        	testl	%eax, %eax
  4026b0: 0f 89 8a 00 00 00            	jns	0x402740 <submitr+0x34a>
  4026b6: 48 b8 45 72 72 6f 72 3a 20 52	movabsq	$5917794173535285829, %rax # imm = 0x52203A726F727245
  4026c0: 48 89 03                     	movq	%rax, (%rbx)
  4026c3: 48 b8 65 73 75 6c 74 20 73 74	movabsq	$8391086215129297765, %rax # imm = 0x747320746C757365
  4026cd: 48 89 43 08                  	movq	%rax, 8(%rbx)
  4026d1: 48 b8 72 69 6e 67 20 63 6f 6e	movabsq	$7957688057412348274, %rax # imm = 0x6E6F6320676E6972
  4026db: 48 89 43 10                  	movq	%rax, 16(%rbx)
  4026df: 48 b8 74 61 69 6e 73 20 61 6e	movabsq	$7953674097058734452, %rax # imm = 0x6E6120736E696174
  4026e9: 48 89 43 18                  	movq	%rax, 24(%rbx)
  4026ed: 48 b8 20 69 6c 6c 65 67 61 6c	movabsq	$7809636914145552672, %rax # imm = 0x6C6167656C6C6920
  4026f7: 48 89 43 20                  	movq	%rax, 32(%rbx)
  4026fb: 48 b8 20 6f 72 20 75 6e 70 72	movabsq	$8246212367049977632, %rax # imm = 0x72706E7520726F20
  402705: 48 89 43 28                  	movq	%rax, 40(%rbx)
  402709: 48 b8 69 6e 74 61 62 6c 65 20	movabsq	$2334391151659085417, %rax # imm = 0x20656C6261746E69
  402713: 48 89 43 30                  	movq	%rax, 48(%rbx)
  402717: 48 b8 63 68 61 72 61 63 74 65	movabsq	$7310577365311121507, %rax # imm = 0x6574636172616863
  402721: 48 89 43 38                  	movq	%rax, 56(%rbx)
  402725: 66 c7 43 40 72 2e            	movw	$11890, 64(%rbx)        # imm = 0x2E72
  40272b: c6 43 42 00                  	movb	$0, 66(%rbx)
  40272f: 89 ef                        	movl	%ebp, %edi
  402731: e8 ea e5 ff ff               	callq	0x400d20 <close@plt>
  402736: b8 ff ff ff ff               	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
  40273b: e9 b1 03 00 00               	jmp	0x402af1 <submitr+0x6fb>
  402740: 4c 89 64 24 08               	movq	%r12, 8(%rsp)
  402745: 48 8d 84 24 40 20 00 00      	leaq	8256(%rsp), %rax
  40274d: 48 89 04 24                  	movq	%rax, (%rsp)
  402751: 4d 89 f9                     	movq	%r15, %r9
  402754: 4d 89 f0                     	movq	%r14, %r8
  402757: b9 08 36 40 00               	movl	$4208136, %ecx          # imm = 0x403608
  40275c: ba 00 20 00 00               	movl	$8192, %edx             # imm = 0x2000
  402761: be 01 00 00 00               	movl	$1, %esi
  402766: 48 8d 7c 24 40               	leaq	64(%rsp), %rdi
  40276b: b8 00 00 00 00               	movl	$0, %eax
  402770: e8 fb e6 ff ff               	callq	0x400e70 <__sprintf_chk@plt>
  402775: 48 8d 7c 24 40               	leaq	64(%rsp), %rdi
  40277a: b8 00 00 00 00               	movl	$0, %eax
  40277f: 48 c7 c1 ff ff ff ff         	movq	$-1, %rcx
  402786: f2 ae                        	repne		scasb	%es:(%rdi), %al
  402788: 48 f7 d1                     	notq	%rcx
  40278b: 48 8d 51 ff                  	leaq	-1(%rcx), %rdx
  40278f: 48 8d 74 24 40               	leaq	64(%rsp), %rsi
  402794: 89 ef                        	movl	%ebp, %edi
  402796: e8 e5 f9 ff ff               	callq	0x402180 <rio_writen>
  40279b: 48 85 c0                     	testq	%rax, %rax
  40279e: 79 6e                        	jns	0x40280e <submitr+0x418>
  4027a0: 48 b8 45 72 72 6f 72 3a 20 43	movabsq	$4836930262966366789, %rax # imm = 0x43203A726F727245
  4027aa: 48 89 03                     	movq	%rax, (%rbx)
  4027ad: 48 b8 6c 69 65 6e 74 20 75 6e	movabsq	$7959303600887654764, %rax # imm = 0x6E7520746E65696C
  4027b7: 48 89 43 08                  	movq	%rax, 8(%rbx)
  4027bb: 48 b8 61 62 6c 65 20 74 6f 20	movabsq	$2337214414117954145, %rax # imm = 0x206F7420656C6261
  4027c5: 48 89 43 10                  	movq	%rax, 16(%rbx)
  4027c9: 48 b8 77 72 69 74 65 20 74 6f	movabsq	$8031079655625290359, %rax # imm = 0x6F74206574697277
  4027d3: 48 89 43 18                  	movq	%rax, 24(%rbx)
  4027d7: 48 b8 20 74 68 65 20 72 65 73	movabsq	$8315177770475353120, %rax # imm = 0x7365722065687420
  4027e1: 48 89 43 20                  	movq	%rax, 32(%rbx)
  4027e5: 48 b8 75 6c 74 20 73 65 72 76	movabsq	$8534995788960656501, %rax # imm = 0x7672657320746C75
  4027ef: 48 89 43 28                  	movq	%rax, 40(%rbx)
  4027f3: 66 c7 43 30 65 72            	movw	$29285, 48(%rbx)        # imm = 0x7265
  4027f9: c6 43 32 00                  	movb	$0, 50(%rbx)
  4027fd: 89 ef                        	movl	%ebp, %edi
  4027ff: e8 1c e5 ff ff               	callq	0x400d20 <close@plt>
  402804: b8 ff ff ff ff               	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
  402809: e9 e3 02 00 00               	jmp	0x402af1 <submitr+0x6fb>
  40280e: 89 ee                        	movl	%ebp, %esi
  402810: 48 8d bc 24 40 80 00 00      	leaq	32832(%rsp), %rdi
  402818: e8 23 f9 ff ff               	callq	0x402140 <rio_readinitb>
  40281d: ba 00 20 00 00               	movl	$8192, %edx             # imm = 0x2000
  402822: 48 8d 74 24 40               	leaq	64(%rsp), %rsi
  402827: 48 8d bc 24 40 80 00 00      	leaq	32832(%rsp), %rdi
  40282f: e8 33 fa ff ff               	callq	0x402267 <rio_readlineb>
  402834: 48 85 c0                     	testq	%rax, %rax
  402837: 7f 7d                        	jg	0x4028b6 <submitr+0x4c0>
  402839: 48 b8 45 72 72 6f 72 3a 20 43	movabsq	$4836930262966366789, %rax # imm = 0x43203A726F727245
  402843: 48 89 03                     	movq	%rax, (%rbx)
  402846: 48 b8 6c 69 65 6e 74 20 75 6e	movabsq	$7959303600887654764, %rax # imm = 0x6E7520746E65696C
  402850: 48 89 43 08                  	movq	%rax, 8(%rbx)
  402854: 48 b8 61 62 6c 65 20 74 6f 20	movabsq	$2337214414117954145, %rax # imm = 0x206F7420656C6261
  40285e: 48 89 43 10                  	movq	%rax, 16(%rbx)
  402862: 48 b8 72 65 61 64 20 66 69 72	movabsq	$8244232882187494770, %rax # imm = 0x7269662064616572
  40286c: 48 89 43 18                  	movq	%rax, 24(%rbx)
  402870: 48 b8 73 74 20 68 65 61 64 65	movabsq	$7306071583668335731, %rax # imm = 0x6564616568207473
  40287a: 48 89 43 20                  	movq	%rax, 32(%rbx)
  40287e: 48 b8 72 20 66 72 6f 6d 20 72	movabsq	$8223693245006618738, %rax # imm = 0x72206D6F72662072
  402888: 48 89 43 28                  	movq	%rax, 40(%rbx)
  40288c: 48 b8 65 73 75 6c 74 20 73 65	movabsq	$7310222304560378725, %rax # imm = 0x657320746C757365
  402896: 48 89 43 30                  	movq	%rax, 48(%rbx)
  40289a: c7 43 38 72 76 65 72         	movl	$1919252082, 56(%rbx)   # imm = 0x72657672
  4028a1: c6 43 3c 00                  	movb	$0, 60(%rbx)
  4028a5: 89 ef                        	movl	%ebp, %edi
  4028a7: e8 74 e4 ff ff               	callq	0x400d20 <close@plt>
  4028ac: b8 ff ff ff ff               	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
  4028b1: e9 3b 02 00 00               	jmp	0x402af1 <submitr+0x6fb>
  4028b6: 4c 8d 84 24 40 60 00 00      	leaq	24640(%rsp), %r8
  4028be: 48 8d 4c 24 2c               	leaq	44(%rsp), %rcx
  4028c3: 48 8d 94 24 40 40 00 00      	leaq	16448(%rsp), %rdx
  4028cb: be 7f 36 40 00               	movl	$4208255, %esi          # imm = 0x40367F
  4028d0: 48 8d 7c 24 40               	leaq	64(%rsp), %rdi
  4028d5: b8 00 00 00 00               	movl	$0, %eax
  4028da: e8 f1 e4 ff ff               	callq	0x400dd0 <__isoc99_sscanf@plt>
  4028df: e9 95 00 00 00               	jmp	0x402979 <submitr+0x583>
  4028e4: ba 00 20 00 00               	movl	$8192, %edx             # imm = 0x2000
  4028e9: 48 8d 74 24 40               	leaq	64(%rsp), %rsi
  4028ee: 48 8d bc 24 40 80 00 00      	leaq	32832(%rsp), %rdi
  4028f6: e8 6c f9 ff ff               	callq	0x402267 <rio_readlineb>
  4028fb: 48 85 c0                     	testq	%rax, %rax
  4028fe: 7f 79                        	jg	0x402979 <submitr+0x583>
  402900: 48 b8 45 72 72 6f 72 3a 20 43	movabsq	$4836930262966366789, %rax # imm = 0x43203A726F727245
  40290a: 48 89 03                     	movq	%rax, (%rbx)
  40290d: 48 b8 6c 69 65 6e 74 20 75 6e	movabsq	$7959303600887654764, %rax # imm = 0x6E7520746E65696C
  402917: 48 89 43 08                  	movq	%rax, 8(%rbx)
  40291b: 48 b8 61 62 6c 65 20 74 6f 20	movabsq	$2337214414117954145, %rax # imm = 0x206F7420656C6261
  402925: 48 89 43 10                  	movq	%rax, 16(%rbx)
  402929: 48 b8 72 65 61 64 20 68 65 61	movabsq	$7018130082659132786, %rax # imm = 0x6165682064616572
  402933: 48 89 43 18                  	movq	%rax, 24(%rbx)
  402937: 48 b8 64 65 72 73 20 66 72 6f	movabsq	$8030593375116879204, %rax # imm = 0x6F72662073726564
  402941: 48 89 43 20                  	movq	%rax, 32(%rbx)
  402945: 48 b8 6d 20 74 68 65 20 72 65	movabsq	$7309940765091962989, %rax # imm = 0x657220656874206D
  40294f: 48 89 43 28                  	movq	%rax, 40(%rbx)
  402953: 48 b8 73 75 6c 74 20 73 65 72	movabsq	$8243121276200973683, %rax # imm = 0x72657320746C7573
  40295d: 48 89 43 30                  	movq	%rax, 48(%rbx)
  402961: c7 43 38 76 65 72 00         	movl	$7497078, 56(%rbx)      # imm = 0x726576
  402968: 89 ef                        	movl	%ebp, %edi
  40296a: e8 b1 e3 ff ff               	callq	0x400d20 <close@plt>
  40296f: b8 ff ff ff ff               	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
  402974: e9 78 01 00 00               	jmp	0x402af1 <submitr+0x6fb>
  402979: 0f b6 44 24 40               	movzbl	64(%rsp), %eax
  40297e: 83 e8 0d                     	subl	$13, %eax
  402981: 75 0f                        	jne	0x402992 <submitr+0x59c>
  402983: 0f b6 44 24 41               	movzbl	65(%rsp), %eax
  402988: 83 e8 0a                     	subl	$10, %eax
  40298b: 75 05                        	jne	0x402992 <submitr+0x59c>
  40298d: 0f b6 44 24 42               	movzbl	66(%rsp), %eax
  402992: 85 c0                        	testl	%eax, %eax
  402994: 0f 85 4a ff ff ff            	jne	0x4028e4 <submitr+0x4ee>
  40299a: ba 00 20 00 00               	movl	$8192, %edx             # imm = 0x2000
  40299f: 48 8d 74 24 40               	leaq	64(%rsp), %rsi
  4029a4: 48 8d bc 24 40 80 00 00      	leaq	32832(%rsp), %rdi
  4029ac: e8 b6 f8 ff ff               	callq	0x402267 <rio_readlineb>
  4029b1: 48 85 c0                     	testq	%rax, %rax
  4029b4: 0f 8f 83 00 00 00            	jg	0x402a3d <submitr+0x647>
  4029ba: 48 b8 45 72 72 6f 72 3a 20 43	movabsq	$4836930262966366789, %rax # imm = 0x43203A726F727245
  4029c4: 48 89 03                     	movq	%rax, (%rbx)
  4029c7: 48 b8 6c 69 65 6e 74 20 75 6e	movabsq	$7959303600887654764, %rax # imm = 0x6E7520746E65696C
  4029d1: 48 89 43 08                  	movq	%rax, 8(%rbx)
  4029d5: 48 b8 61 62 6c 65 20 74 6f 20	movabsq	$2337214414117954145, %rax # imm = 0x206F7420656C6261
  4029df: 48 89 43 10                  	movq	%rax, 16(%rbx)
  4029e3: 48 b8 72 65 61 64 20 73 74 61	movabsq	$7022364301937698162, %rax # imm = 0x6174732064616572
  4029ed: 48 89 43 18                  	movq	%rax, 24(%rbx)
  4029f1: 48 b8 74 75 73 20 6d 65 73 73	movabsq	$8319104456053716340, %rax # imm = 0x7373656D20737574
  4029fb: 48 89 43 20                  	movq	%rax, 32(%rbx)
  4029ff: 48 b8 61 67 65 20 66 72 6f 6d	movabsq	$7885647255504775009, %rax # imm = 0x6D6F726620656761
  402a09: 48 89 43 28                  	movq	%rax, 40(%rbx)
  402a0d: 48 b8 20 72 65 73 75 6c 74 20	movabsq	$2338613358215131680, %rax # imm = 0x20746C7573657220
  402a17: 48 89 43 30                  	movq	%rax, 48(%rbx)
  402a1b: c7 43 38 73 65 72 76         	movl	$1987208563, 56(%rbx)   # imm = 0x76726573
  402a22: 66 c7 43 3c 65 72            	movw	$29285, 60(%rbx)        # imm = 0x7265
  402a28: c6 43 3e 00                  	movb	$0, 62(%rbx)
  402a2c: 89 ef                        	movl	%ebp, %edi
  402a2e: e8 ed e2 ff ff               	callq	0x400d20 <close@plt>
  402a33: b8 ff ff ff ff               	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
  402a38: e9 b4 00 00 00               	jmp	0x402af1 <submitr+0x6fb>
  402a3d: 44 8b 44 24 2c               	movl	44(%rsp), %r8d
  402a42: 41 81 f8 c8 00 00 00         	cmpl	$200, %r8d
  402a49: 74 34                        	je	0x402a7f <submitr+0x689>
  402a4b: 4c 8d 8c 24 40 60 00 00      	leaq	24640(%rsp), %r9
  402a53: b9 48 36 40 00               	movl	$4208200, %ecx          # imm = 0x403648
  402a58: 48 c7 c2 ff ff ff ff         	movq	$-1, %rdx
  402a5f: be 01 00 00 00               	movl	$1, %esi
  402a64: 48 89 df                     	movq	%rbx, %rdi
  402a67: b8 00 00 00 00               	movl	$0, %eax
  402a6c: e8 ff e3 ff ff               	callq	0x400e70 <__sprintf_chk@plt>
  402a71: 89 ef                        	movl	%ebp, %edi
  402a73: e8 a8 e2 ff ff               	callq	0x400d20 <close@plt>
  402a78: b8 ff ff ff ff               	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
  402a7d: eb 72                        	jmp	0x402af1 <submitr+0x6fb>
  402a7f: 48 8d 74 24 40               	leaq	64(%rsp), %rsi
  402a84: 48 89 df                     	movq	%rbx, %rdi
  402a87: e8 24 e2 ff ff               	callq	0x400cb0 <strcpy@plt>
  402a8c: 89 ef                        	movl	%ebp, %edi
  402a8e: e8 8d e2 ff ff               	callq	0x400d20 <close@plt>
  402a93: 0f b6 13                     	movzbl	(%rbx), %edx
  402a96: 83 ea 4f                     	subl	$79, %edx
  402a99: 89 d1                        	movl	%edx, %ecx
  402a9b: 85 d2                        	testl	%edx, %edx
  402a9d: 75 16                        	jne	0x402ab5 <submitr+0x6bf>
  402a9f: 0f b6 4b 01                  	movzbl	1(%rbx), %ecx
  402aa3: 83 e9 4b                     	subl	$75, %ecx
  402aa6: 75 0d                        	jne	0x402ab5 <submitr+0x6bf>
  402aa8: 0f b6 4b 02                  	movzbl	2(%rbx), %ecx
  402aac: 83 e9 0a                     	subl	$10, %ecx
  402aaf: 75 04                        	jne	0x402ab5 <submitr+0x6bf>
  402ab1: 0f b6 4b 03                  	movzbl	3(%rbx), %ecx
  402ab5: b8 00 00 00 00               	movl	$0, %eax
  402aba: 85 c9                        	testl	%ecx, %ecx
  402abc: 74 33                        	je	0x402af1 <submitr+0x6fb>
  402abe: bf 90 36 40 00               	movl	$4208272, %edi          # imm = 0x403690
  402ac3: b9 05 00 00 00               	movl	$5, %ecx
  402ac8: 48 89 de                     	movq	%rbx, %rsi
  402acb: f3 a6                        	rep		cmpsb	%es:(%rdi), (%rsi)
  402acd: 40 0f 97 c6                  	seta	%sil
  402ad1: 0f 92 c1                     	setb	%cl
  402ad4: 40 38 ce                     	cmpb	%cl, %sil
  402ad7: 74 18                        	je	0x402af1 <submitr+0x6fb>
  402ad9: 85 d2                        	testl	%edx, %edx
  402adb: 75 0d                        	jne	0x402aea <submitr+0x6f4>
  402add: 0f b6 53 01                  	movzbl	1(%rbx), %edx
  402ae1: 83 ea 4b                     	subl	$75, %edx
  402ae4: 75 04                        	jne	0x402aea <submitr+0x6f4>
  402ae6: 0f b6 53 02                  	movzbl	2(%rbx), %edx
  402aea: 83 fa 01                     	cmpl	$1, %edx
  402aed: 19 c0                        	sbbl	%eax, %eax
  402aef: f7 d0                        	notl	%eax
  402af1: 48 8b 9c 24 58 a0 00 00      	movq	41048(%rsp), %rbx
  402af9: 64 48 33 1c 25 28 00 00 00   	xorq	%fs:40, %rbx
  402b02: 74 05                        	je	0x402b09 <submitr+0x713>
  402b04: e8 d7 e1 ff ff               	callq	0x400ce0 <__stack_chk_fail@plt>
  402b09: 48 81 c4 68 a0 00 00         	addq	$41064, %rsp            # imm = 0xA068
  402b10: 5b                           	popq	%rbx
  402b11: 5d                           	popq	%rbp
  402b12: 41 5c                        	popq	%r12
  402b14: 41 5d                        	popq	%r13
  402b16: 41 5e                        	popq	%r14
  402b18: 41 5f                        	popq	%r15
  402b1a: c3                           	retq

0000000000402b1b <init_timeout>:
  402b1b: 53                           	pushq	%rbx
  402b1c: 89 fb                        	movl	%edi, %ebx
  402b1e: 85 ff                        	testl	%edi, %edi
  402b20: 74 20                        	je	0x402b42 <init_timeout+0x27>
  402b22: 85 ff                        	testl	%edi, %edi
  402b24: b8 00 00 00 00               	movl	$0, %eax
  402b29: 0f 48 d8                     	cmovsl	%eax, %ebx
  402b2c: be 52 21 40 00               	movl	$4202834, %esi          # imm = 0x402152
  402b31: bf 0e 00 00 00               	movl	$14, %edi
  402b36: e8 15 e2 ff ff               	callq	0x400d50 <signal@plt>
  402b3b: 89 df                        	movl	%ebx, %edi
  402b3d: e8 ce e1 ff ff               	callq	0x400d10 <alarm@plt>
  402b42: 5b                           	popq	%rbx
  402b43: c3                           	retq

0000000000402b44 <init_driver>:
  402b44: 55                           	pushq	%rbp
  402b45: 53                           	pushq	%rbx
  402b46: 48 83 ec 28                  	subq	$40, %rsp
  402b4a: 48 89 fd                     	movq	%rdi, %rbp
  402b4d: 64 48 8b 04 25 28 00 00 00   	movq	%fs:40, %rax
  402b56: 48 89 44 24 18               	movq	%rax, 24(%rsp)
  402b5b: 31 c0                        	xorl	%eax, %eax
  402b5d: be 01 00 00 00               	movl	$1, %esi
  402b62: bf 0d 00 00 00               	movl	$13, %edi
  402b67: e8 e4 e1 ff ff               	callq	0x400d50 <signal@plt>
  402b6c: be 01 00 00 00               	movl	$1, %esi
  402b71: bf 1d 00 00 00               	movl	$29, %edi
  402b76: e8 d5 e1 ff ff               	callq	0x400d50 <signal@plt>
  402b7b: be 01 00 00 00               	movl	$1, %esi
  402b80: bf 1d 00 00 00               	movl	$29, %edi
  402b85: e8 c6 e1 ff ff               	callq	0x400d50 <signal@plt>
  402b8a: ba 00 00 00 00               	movl	$0, %edx
  402b8f: be 01 00 00 00               	movl	$1, %esi
  402b94: bf 02 00 00 00               	movl	$2, %edi
  402b99: e8 e2 e2 ff ff               	callq	0x400e80 <socket@plt>
  402b9e: 89 c3                        	movl	%eax, %ebx
  402ba0: 85 c0                        	testl	%eax, %eax
  402ba2: 79 4f                        	jns	0x402bf3 <init_driver+0xaf>
  402ba4: 48 b8 45 72 72 6f 72 3a 20 43	movabsq	$4836930262966366789, %rax # imm = 0x43203A726F727245
  402bae: 48 89 45 00                  	movq	%rax, (%rbp)
  402bb2: 48 b8 6c 69 65 6e 74 20 75 6e	movabsq	$7959303600887654764, %rax # imm = 0x6E7520746E65696C
  402bbc: 48 89 45 08                  	movq	%rax, 8(%rbp)
  402bc0: 48 b8 61 62 6c 65 20 74 6f 20	movabsq	$2337214414117954145, %rax # imm = 0x206F7420656C6261
  402bca: 48 89 45 10                  	movq	%rax, 16(%rbp)
  402bce: 48 b8 63 72 65 61 74 65 20 73	movabsq	$8295742064141103715, %rax # imm = 0x7320657461657263
  402bd8: 48 89 45 18                  	movq	%rax, 24(%rbp)
  402bdc: c7 45 20 6f 63 6b 65         	movl	$1701536623, 32(%rbp)   # imm = 0x656B636F
  402be3: 66 c7 45 24 74 00            	movw	$116, 36(%rbp)
  402be9: b8 ff ff ff ff               	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
  402bee: e9 28 01 00 00               	jmp	0x402d1b <init_driver+0x1d7>
  402bf3: bf 95 36 40 00               	movl	$4208277, %edi          # imm = 0x403695
  402bf8: e8 63 e1 ff ff               	callq	0x400d60 <gethostbyname@plt>
  402bfd: 48 85 c0                     	testq	%rax, %rax
  402c00: 75 68                        	jne	0x402c6a <init_driver+0x126>
  402c02: 48 b8 45 72 72 6f 72 3a 20 44	movabsq	$4908987857004294725, %rax # imm = 0x44203A726F727245
  402c0c: 48 89 45 00                  	movq	%rax, (%rbp)
  402c10: 48 b8 4e 53 20 69 73 20 75 6e	movabsq	$7959303596504273742, %rax # imm = 0x6E7520736920534E
  402c1a: 48 89 45 08                  	movq	%rax, 8(%rbp)
  402c1e: 48 b8 61 62 6c 65 20 74 6f 20	movabsq	$2337214414117954145, %rax # imm = 0x206F7420656C6261
  402c28: 48 89 45 10                  	movq	%rax, 16(%rbp)
  402c2c: 48 b8 72 65 73 6f 6c 76 65 20	movabsq	$2334402189959849330, %rax # imm = 0x2065766C6F736572
  402c36: 48 89 45 18                  	movq	%rax, 24(%rbp)
  402c3a: 48 b8 73 65 72 76 65 72 20 61	movabsq	$6998719601038222707, %rax # imm = 0x6120726576726573
  402c44: 48 89 45 20                  	movq	%rax, 32(%rbp)
  402c48: c7 45 28 64 64 72 65         	movl	$1701995620, 40(%rbp)   # imm = 0x65726464
  402c4f: 66 c7 45 2c 73 73            	movw	$29555, 44(%rbp)        # imm = 0x7373
  402c55: c6 45 2e 00                  	movb	$0, 46(%rbp)
  402c59: 89 df                        	movl	%ebx, %edi
  402c5b: e8 c0 e0 ff ff               	callq	0x400d20 <close@plt>
  402c60: b8 ff ff ff ff               	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
  402c65: e9 b1 00 00 00               	jmp	0x402d1b <init_driver+0x1d7>
  402c6a: 48 c7 04 24 00 00 00 00      	movq	$0, (%rsp)
  402c72: 48 c7 44 24 08 00 00 00 00   	movq	$0, 8(%rsp)
  402c7b: 66 c7 04 24 02 00            	movw	$2, (%rsp)
  402c81: 48 63 50 14                  	movslq	20(%rax), %rdx
  402c85: 48 8b 40 18                  	movq	24(%rax), %rax
  402c89: 48 8b 30                     	movq	(%rax), %rsi
  402c8c: 48 8d 7c 24 04               	leaq	4(%rsp), %rdi
  402c91: b9 0c 00 00 00               	movl	$12, %ecx
  402c96: e8 d5 e0 ff ff               	callq	0x400d70 <__memmove_chk@plt>
  402c9b: 66 c7 44 24 02 3c 9a         	movw	$39484, 2(%rsp)         # imm = 0x9A3C
  402ca2: ba 10 00 00 00               	movl	$16, %edx
  402ca7: 48 89 e6                     	movq	%rsp, %rsi
  402caa: 89 df                        	movl	%ebx, %edi
  402cac: e8 9f e1 ff ff               	callq	0x400e50 <connect@plt>
  402cb1: 85 c0                        	testl	%eax, %eax
  402cb3: 79 50                        	jns	0x402d05 <init_driver+0x1c1>
  402cb5: 48 b8 45 72 72 6f 72 3a 20 55	movabsq	$6133966955649069637, %rax # imm = 0x55203A726F727245
  402cbf: 48 89 45 00                  	movq	%rax, (%rbp)
  402cc3: 48 b8 6e 61 62 6c 65 20 74 6f	movabsq	$8031079655490609518, %rax # imm = 0x6F7420656C62616E
  402ccd: 48 89 45 08                  	movq	%rax, 8(%rbp)
  402cd1: 48 b8 20 63 6f 6e 6e 65 63 74	movabsq	$8386658456067597088, %rax # imm = 0x7463656E6E6F6320
  402cdb: 48 89 45 10                  	movq	%rax, 16(%rbp)
  402cdf: 48 b8 20 74 6f 20 73 65 72 76	movabsq	$8534995788960330784, %rax # imm = 0x76726573206F7420
  402ce9: 48 89 45 18                  	movq	%rax, 24(%rbp)
  402ced: 66 c7 45 20 65 72            	movw	$29285, 32(%rbp)        # imm = 0x7265
  402cf3: c6 45 22 00                  	movb	$0, 34(%rbp)
  402cf7: 89 df                        	movl	%ebx, %edi
  402cf9: e8 22 e0 ff ff               	callq	0x400d20 <close@plt>
  402cfe: b8 ff ff ff ff               	movl	$4294967295, %eax       # imm = 0xFFFFFFFF
  402d03: eb 16                        	jmp	0x402d1b <init_driver+0x1d7>
  402d05: 89 df                        	movl	%ebx, %edi
  402d07: e8 14 e0 ff ff               	callq	0x400d20 <close@plt>
  402d0c: 66 c7 45 00 4f 4b            	movw	$19279, (%rbp)          # imm = 0x4B4F
  402d12: c6 45 02 00                  	movb	$0, 2(%rbp)
  402d16: b8 00 00 00 00               	movl	$0, %eax
  402d1b: 48 8b 4c 24 18               	movq	24(%rsp), %rcx
  402d20: 64 48 33 0c 25 28 00 00 00   	xorq	%fs:40, %rcx
  402d29: 74 05                        	je	0x402d30 <init_driver+0x1ec>
  402d2b: e8 b0 df ff ff               	callq	0x400ce0 <__stack_chk_fail@plt>
  402d30: 48 83 c4 28                  	addq	$40, %rsp
  402d34: 5b                           	popq	%rbx
  402d35: 5d                           	popq	%rbp
  402d36: c3                           	retq

0000000000402d37 <driver_post>:
  402d37: 53                           	pushq	%rbx
  402d38: 48 83 ec 10                  	subq	$16, %rsp
  402d3c: 4c 89 cb                     	movq	%r9, %rbx
  402d3f: 45 85 c0                     	testl	%r8d, %r8d
  402d42: 74 27                        	je	0x402d6b <driver_post+0x34>
  402d44: 48 89 ca                     	movq	%rcx, %rdx
  402d47: be ad 36 40 00               	movl	$4208301, %esi          # imm = 0x4036AD
  402d4c: bf 01 00 00 00               	movl	$1, %edi
  402d51: b8 00 00 00 00               	movl	$0, %eax
  402d56: e8 95 e0 ff ff               	callq	0x400df0 <__printf_chk@plt>
  402d5b: 66 c7 03 4f 4b               	movw	$19279, (%rbx)          # imm = 0x4B4F
  402d60: c6 43 02 00                  	movb	$0, 2(%rbx)
  402d64: b8 00 00 00 00               	movl	$0, %eax
  402d69: eb 39                        	jmp	0x402da4 <driver_post+0x6d>
  402d6b: 48 85 ff                     	testq	%rdi, %rdi
  402d6e: 74 26                        	je	0x402d96 <driver_post+0x5f>
  402d70: 80 3f 00                     	cmpb	$0, (%rdi)
  402d73: 74 21                        	je	0x402d96 <driver_post+0x5f>
  402d75: 4c 89 0c 24                  	movq	%r9, (%rsp)
  402d79: 49 89 c9                     	movq	%rcx, %r9
  402d7c: 49 89 d0                     	movq	%rdx, %r8
  402d7f: 48 89 f9                     	movq	%rdi, %rcx
  402d82: 48 89 f2                     	movq	%rsi, %rdx
  402d85: be 9a 3c 00 00               	movl	$15514, %esi            # imm = 0x3C9A
  402d8a: bf 95 36 40 00               	movl	$4208277, %edi          # imm = 0x403695
  402d8f: e8 62 f6 ff ff               	callq	0x4023f6 <submitr>
  402d94: eb 0e                        	jmp	0x402da4 <driver_post+0x6d>
  402d96: 66 c7 03 4f 4b               	movw	$19279, (%rbx)          # imm = 0x4B4F
  402d9b: c6 43 02 00                  	movb	$0, 2(%rbx)
  402d9f: b8 00 00 00 00               	movl	$0, %eax
  402da4: 48 83 c4 10                  	addq	$16, %rsp
  402da8: 5b                           	popq	%rbx
  402da9: c3                           	retq
  402daa: 90                           	nop
  402dab: 90                           	nop

0000000000402dac <check>:
  402dac: 89 fa                        	movl	%edi, %edx
  402dae: c1 ea 1c                     	shrl	$28, %edx
  402db1: b8 00 00 00 00               	movl	$0, %eax
  402db6: b9 00 00 00 00               	movl	$0, %ecx
  402dbb: 85 d2                        	testl	%edx, %edx
  402dbd: 75 0d                        	jne	0x402dcc <check+0x20>
  402dbf: eb 1b                        	jmp	0x402ddc <check+0x30>
  402dc1: 89 f8                        	movl	%edi, %eax
  402dc3: d3 e8                        	shrl	%cl, %eax
  402dc5: 3c 0a                        	cmpb	$10, %al
  402dc7: 74 0e                        	je	0x402dd7 <check+0x2b>
  402dc9: 83 c1 08                     	addl	$8, %ecx
  402dcc: 83 f9 1f                     	cmpl	$31, %ecx
  402dcf: 7e f0                        	jle	0x402dc1 <check+0x15>
  402dd1: b8 01 00 00 00               	movl	$1, %eax
  402dd6: c3                           	retq
  402dd7: b8 00 00 00 00               	movl	$0, %eax
  402ddc: f3 c3                        	rep		retq

0000000000402dde <gencookie>:
  402dde: 53                           	pushq	%rbx
  402ddf: 83 c7 01                     	addl	$1, %edi
  402de2: e8 a9 de ff ff               	callq	0x400c90 <srandom@plt>
  402de7: e8 c4 df ff ff               	callq	0x400db0 <random@plt>
  402dec: 89 c3                        	movl	%eax, %ebx
  402dee: 89 c7                        	movl	%eax, %edi
  402df0: e8 b7 ff ff ff               	callq	0x402dac <check>
  402df5: 85 c0                        	testl	%eax, %eax
  402df7: 74 ee                        	je	0x402de7 <gencookie+0x9>
  402df9: 89 d8                        	movl	%ebx, %eax
  402dfb: 5b                           	popq	%rbx
  402dfc: c3                           	retq
  402dfd: 90                           	nop
  402dfe: 90                           	nop
  402dff: 90                           	nop

0000000000402e00 <__libc_csu_init>:
  402e00: 48 89 6c 24 d8               	movq	%rbp, -40(%rsp)
  402e05: 4c 89 64 24 e0               	movq	%r12, -32(%rsp)
  402e0a: 48 8d 2d ef 1f 20 00         	leaq	2105327(%rip), %rbp     # 0x604e00 <__do_global_dtors_aux_fini_array_entry>
  402e11: 4c 8d 25 e0 1f 20 00         	leaq	2105312(%rip), %r12     # 0x604df8 <__init_array_start>
  402e18: 4c 89 6c 24 e8               	movq	%r13, -24(%rsp)
  402e1d: 4c 89 74 24 f0               	movq	%r14, -16(%rsp)
  402e22: 4c 89 7c 24 f8               	movq	%r15, -8(%rsp)
  402e27: 48 89 5c 24 d0               	movq	%rbx, -48(%rsp)
  402e2c: 48 83 ec 38                  	subq	$56, %rsp
  402e30: 4c 29 e5                     	subq	%r12, %rbp
  402e33: 41 89 fd                     	movl	%edi, %r13d
  402e36: 49 89 f6                     	movq	%rsi, %r14
  402e39: 48 c1 fd 03                  	sarq	$3, %rbp
  402e3d: 49 89 d7                     	movq	%rdx, %r15
  402e40: e8 03 de ff ff               	callq	0x400c48 <_init>
  402e45: 48 85 ed                     	testq	%rbp, %rbp
  402e48: 74 1c                        	je	0x402e66 <__libc_csu_init+0x66>
  402e4a: 31 db                        	xorl	%ebx, %ebx
  402e4c: 0f 1f 40 00                  	nopl	(%rax)
  402e50: 4c 89 fa                     	movq	%r15, %rdx
  402e53: 4c 89 f6                     	movq	%r14, %rsi
  402e56: 44 89 ef                     	movl	%r13d, %edi
  402e59: 41 ff 14 dc                  	callq	*(%r12,%rbx,8)
  402e5d: 48 83 c3 01                  	addq	$1, %rbx
  402e61: 48 39 eb                     	cmpq	%rbp, %rbx
  402e64: 75 ea                        	jne	0x402e50 <__libc_csu_init+0x50>
  402e66: 48 8b 5c 24 08               	movq	8(%rsp), %rbx
  402e6b: 48 8b 6c 24 10               	movq	16(%rsp), %rbp
  402e70: 4c 8b 64 24 18               	movq	24(%rsp), %r12
  402e75: 4c 8b 6c 24 20               	movq	32(%rsp), %r13
  402e7a: 4c 8b 74 24 28               	movq	40(%rsp), %r14
  402e7f: 4c 8b 7c 24 30               	movq	48(%rsp), %r15
  402e84: 48 83 c4 38                  	addq	$56, %rsp
  402e88: c3                           	retq
  402e89: 0f 1f 80 00 00 00 00         	nopl	(%rax)

0000000000402e90 <__libc_csu_fini>:
  402e90: f3 c3                        	rep		retq
  402e92: 90                           	nop
  402e93: 90                           	nop

Disassembly of section .fini:

0000000000402e94 <_fini>:
  402e94: 48 83 ec 08                  	subq	$8, %rsp
  402e98: 48 83 c4 08                  	addq	$8, %rsp
  402e9c: c3                           	retq
