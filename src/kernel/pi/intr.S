.arm
.extern isr_handle
.global interrupt_vector

interrupt_vector:
sub     r14, #4
/* Nicht gebankte Register speichern */
push    {r0 - r12, r14}

/* Supervisor-R13/R14/SPSR und CPSR speichern */
msr     cpsr_ctl, #0xD3
mrs     r1, spsr
mov     r2, r13
mov     r3, r14
msr     cpsr_ctl, #0xD2
mrs     r0, spsr
push    {r0 - r3}

/* User-R13/R14 speichern */
stmdb   r13, {r13, r14}^
sub     r13, #8

/* IRQ behandeln */
mov     r0, r13
bl      isr_handle
mov     r13, r0

/* User-R13/R14 laden */
ldmia   r13, {r13, r14}^
add     r13, #8

/* Supervisor-R13/R14/SPSR und CPSR laden */
pop     {r0 - r3}
msr     spsr_all, r0
msr     cpsr_ctl, #0xD3
msr     spsr_all, r1
mov     r13, r2
mov     r14, r3
msr     cpsr_all, #0xD2

/* Nicht gebankte Register laden und zurÃ¼ckkehren */
pop     {r0 - r12, r14}
movs    r15, r14
