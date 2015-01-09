.globl halt

halt:
	.func halt

_loop:
	/* Disable IRQs and FIQs.  */
	msr cpsr_c, #0x80 | 0x40

	wfi

	b _loop
	.endfunc

.globl pause
pause:
	.func pause
	wfi             
	mov pc, lr
	.endfunc
