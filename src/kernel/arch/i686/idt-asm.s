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
	pushl $\n
	pushl %eax
	pushl %ebx
	pushl %ecx
	pushl %edx
	movw %ds, %ax
	pushl %eax

	# TODO: don't hardcode the segment in case it changes in the future
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss

	# Make sure the stack is 16-byte aligned
	movl %esp, %ebp
	andl $-16, %esp
	addl $12, %esp
	pushl %ebp

	movl $\n, %eax
	movl handlers(,%eax,4), %eax
	call *%eax

	movl %ebp, %esp

	popl %eax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss

	popl %edx
	popl %ecx
	popl %ebx
	popl %eax
	addl $8, %esp

	iret
.size handler\n, . - handler\n
.endm

handler 0
handler 1
handler 2
handler 3
handler 4
handler 5
handler 6
handler 7
handler 8 1
handler 9
handler 10 1
handler 11 1
handler 12 1
handler 13 1
handler 14 1
handler 16
handler 17 1
handler 18
handler 19
handler 20
