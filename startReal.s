
.set ALIGN,    1<<0
.set MEMINFO,  1<<1       
.set GRAPH,    1<<2
.set FRAME,    1<<12
.set HEADADDR,    1<<16
.set MAGIC,    0x1BADB002      
.set FLAGS,    ALIGN | MEMINFO | GRAPH 
/* .set FLAGS,    0b111 */
.set CHECKSUM, -(MAGIC + FLAGS) 
.set MODETYPE, 0
.set WIDTH,    1024
.set HEIGHT,   768
.set DEPTH,    32
.set FBADDR,   0x200000

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
.skip 20
.long MODETYPE
.long WIDTH
.long HEIGHT
.long DEPTH

.section .bss
.align 4
stack_bottom:
.skip 16384
stack_top:
 
.section .text
.global _start
.type _start, @function

_start:
	mov $stack_top, %esp
	movl %ebx, (0x7e00)
	call init
	cli
1:	hlt
	jmp 1b

.size _start, . - _start
