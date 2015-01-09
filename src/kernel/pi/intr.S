.globl enable
.globl disable
.globl restore


enable:
	.func enable
	cpsie i
	mov pc, lr
	.endfunc

disable:
	.func disable
	mrs r0, cpsr
	cpsid i
	mov pc, lr
	.endfunc

restore:
	.func restore
	msr cpsr_c, r0
	mov pc, lr
	.endfunc