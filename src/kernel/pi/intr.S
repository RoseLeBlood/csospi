.arm
.extern isr_handle
.global interrupt_vector
.globl dmb

#define ARM_MODE_SYS    0x1F

interrupt_vector:
.func interrupt_vector

	sub lr, lr, #4
	 
	srsdb #ARM_MODE_SYS!
	cpsid if, #ARM_MODE_SYS

	push {r0-r4, r12, lr}

	/* Execute a data memory barrier, as per the BCM2835 documentation.  */
	bl dmb

	/* Call the C interrupt dispatching code. */
	bl isr_handle

	/* Execute a data memory barrier, as per the BCM2835 documentation.  */
	bl dmb


	add sp, sp, r4

	pop {r0-r4, r12, lr}

	rfeia sp!
	.endfunc



dmb:
	.func dmb
	mov	r12, #0
	mcr	p15, 0, r12, c7, c10, 5
	mov 	pc, lr
	.endfunc
