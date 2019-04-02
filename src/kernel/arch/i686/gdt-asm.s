.section .data
gdt:
limit: .short 0
offset: .long 0

.section .text
.global lgdt
.type lgdt, @function
lgdt:
	movl 4(%esp), %eax
	movl %eax, offset
	movw 8(%esp), %ax
	movw %ax, limit
	lgdt gdt
	ret
.size lgdt, . - lgdt

.global reloadsegs
.type reloadsegs, @function
reloadsegs:
	movw 4(%esp), %ax
	shlw $3, %ax
	movw %ax, %ds
	jmp %ds:0f
0:
	movw 8(%esp), %ax
	shlw $3, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss
	ret
.size reloadsegs, . - reloadsegs
