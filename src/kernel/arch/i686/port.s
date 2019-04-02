.section .text
.global outb
.type outb, @function
outb:
	movl 4(%esp), %edx
	movb 8(%esp), %al
	outb %al, %dx
	ret
.size outb, . - outb

.global outw
.type outw, @function
outw:
	movl 4(%esp), %edx
	movw 8(%esp), %ax
	outw %ax, %dx
	ret
.size outw, . - outw

.global outl
.type outl, @function
outl:
	movl 4(%esp), %edx
	movl 8(%esp), %eax
	outl %eax, %dx
	ret
.size outl, . - outl
