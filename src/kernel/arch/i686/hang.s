.global hang
.type hang, @function
hang:
	cli
0:	hlt
	jmp 0b
.size hang, . - hang
