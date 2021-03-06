/* Basic structure taken from OSDev wiki */
.set ALIGN, 1 << 0 /* align to page boundaries */
.set MEMINFO, 1 << 1 /* provide memory map */
.set FLAGS, ALIGN | MEMINFO
.set MAGIC, 0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384 /* 16 KiB */
stack_top:

.section .data
exited: .string "Kernel exited"

.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp

	# The stack is already 16-byte aligned at this point
	call kinit
	# TODO: set up PIC so we don't have to do this
	movb $0xFF, %al
	outb %al, $0xA1
	outb %al, $0x21

	sti

	call kmain

	subl $12, %esp
	pushl $exited
	call panic
.size _start, . - _start
