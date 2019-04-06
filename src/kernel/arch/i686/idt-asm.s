.section .data
idt:
limit: .short 0
offset: .long 0

fmt: .string "%X"

.section .text
.global lidt
.type lidt, @function
lidt:
	movl 4(%esp), %eax
	movl %eax, offset
	movw 8(%esp), %ax
	decw %ax
	movw %ax, limit
	lidt idt
	ret
.size lidt, . - lidt

.macro handler n err=0
.global handler\n
.type handler\n, @function
handler\n :
.if !\err
	pushl $0
.endif
	pushl %eax
	pushl %ecx
	pushl %edx
	pushl $\n
	pushl %esp
	movl $\n, %eax
	shll $3, %eax
	addl $handlers, %eax

	call *(%eax)

	popl %esp
	addl $4, %esp
	popl %edx
	popl %ecx
	popl %eax
.if !\err
	addl $4, %esp
.endif
	iret
.size handler\n, . - handler\n
.endm

handler 0
handler 1
handler 13 1
