#include <kernel/isr.h>
#include <iob.h>

#include <stdio.h>

#define IC_REGS ((volatile uint32_t *)0x14000000)
#define RPI_INTERRUPT_CONTROLLER_BASE   0x2000B200


typedef struct {
	unsigned long	IRQBasic;	// Pending 0
	unsigned long	Pending1;
	unsigned long	Pending2;
	unsigned long	FIQCtrl;
	unsigned long	Enable1;
	unsigned long	Enable2;
	unsigned long	EnableBasic;
	unsigned long	Disable1;
	unsigned long	Disable2;
	unsigned long	DisableBasic;
} BCM2835_INTC_REGS;

static volatile BCM2835_INTC_REGS * const pRegs = (BCM2835_INTC_REGS *) (0x2000B200);

struct isr_handler_struct
{
	isr_t interrupt_handlers;
	void* userdata;
};




struct isr_handler_struct  interrupt_handlers[BCM2835_INTC_TOTAL_IRQ];

static void irqEnable() {
	__asm volatile("mrs 	r0,cpsr");		// Read in the cpsr register.
	__asm volatile("bic		r0,r0,#0x80");	// Clear bit 8, (0x80) -- Causes IRQs to be enabled.
	__asm volatile("msr		cpsr_c, r0");	// Write it back to the CPSR register
}

static void irqDisable() {
	__asm volatile("mrs		r0,cpsr");		// Read in the cpsr register.
	__asm volatile("orr		r0,r0,#0x80");	// Set bit 8, (0x80) -- Causes IRQs to be disabled.
	__asm volatile("msr		cpsr_c, r0");	// Write it back to the CPSR register.

}
int 	enable_irq				()
{
	irqEnable();
	return 0;
}
int 	disable_irq				()
{
	irqDisable();
	return 0;
}
int 	init_isr	()
{
	int i;
	for(i = 0; i < BCM2835_INTC_TOTAL_IRQ; i++)
	{
		interrupt_handlers[i].interrupt_handlers 	= NULL;
		interrupt_handlers[i].userdata			    = (void *) 0;
	}
	return 0;
}


int set_handler(uint8_t n, isr_t handler)
{
	return set_handlerex(n, handler, NULL);
}
int set_handlerex(uint8_t n, isr_t handler, void* userdata)
{
	if(n > 71)
		return -1;

	disable_irq();
	{
		interrupt_handlers[n].interrupt_handlers = handler;
    	interrupt_handlers[n].userdata = userdata;
	}
	enable_irq();
	return 0;
}
int set_on_irq(int nIRQ) {
	/* Datasheet says "All other bits are unaffected", and I'm counting on that. */
	unsigned int mask=1<<(nIRQ%32);

	if(nIRQ >=0 && nIRQ <=31) {
		pRegs->Enable1 = mask;
	} else
	if(nIRQ >=32 && nIRQ <=63){
		pRegs->Enable2 = mask;
	} else
	if(nIRQ >= 64 && nIRQ <= 71) {	// Basic IRQ enables
		pRegs->EnableBasic = mask;
	} else
		return -1;

	return 0;
}
int set_off_irq(int nIRQ) {
	/* Datasheet says "All other bits are unaffected", and I'm counting on that. */
	unsigned int mask=1<<(nIRQ%32);

	if(nIRQ >=0 && nIRQ <=31) {
		pRegs->Disable1 = mask;
	} else
	if(nIRQ >=32 && nIRQ <=63){
		pRegs->Disable2 = mask;
	} else
	if(nIRQ >= 64 && nIRQ <= 71) {
		pRegs->DisableBasic = mask;
	} else
		return -1;

	return 0;
}













#define clz(a) \
 ({ unsigned long __value, __arg = (a); \
     asm ("clz\t%0, %1": "=r" (__value): "r" (__arg)); \
     __value; })
struct register_t* __attribute__((interrupt("IRQ"))) isr_handle(struct register_t* state)
{
    register unsigned long ulMaskedStatus;
	register unsigned long irqNumber;

	ulMaskedStatus = pRegs->IRQBasic;

	/* Bits 7 through 0 in IRQBasic represent interrupts 64-71 */
	if (ulMaskedStatus & 0xFF) {
		irqNumber=64 + 31;
	}

	/* Bit 8 in IRQBasic indicates interrupts in Pending1 (interrupts 31-0) */
	else if(ulMaskedStatus & 0x100) {
		ulMaskedStatus = pRegs->Pending1;
		irqNumber = 0 + 31;
	}

	/* Bit 9 in IRQBasic indicates interrupts in Pending2 (interrupts 63-32) */
	else if(ulMaskedStatus & 0x200) {
		ulMaskedStatus = pRegs->Pending2;
		irqNumber = 32 + 31;
	}

	else {
		// No interrupt avaialbe, so just return.
		return state;
	}

	/* Keep only least significant bit, in case multiple interrupts have occured */
	ulMaskedStatus&=-ulMaskedStatus;
	/* Some magic to determine number of interrupt to serve */
	irqNumber=irqNumber-clz(ulMaskedStatus);
  	
  	isr_t handler = interrupt_handlers[irqNumber].interrupt_handlers;
  	if(handler != NULL)
    	return handler(state, interrupt_handlers[irqNumber].userdata);
 

    return state;
}
void __attribute__((interrupt("FIQ"))) fast_interrupt_vector(void)
{

}

void __attribute__((interrupt("ABORT"))) reset_vector(void)
{

}

void __attribute__((interrupt("UNDEF"))) undefined_instruction_vector(void)
{
    while( 1 )
    {
        /* Do Nothing! */
    }
}

void __attribute__((interrupt("SWI"))) software_interrupt_vector(void)
{
    while( 1 )
    {
        /* Do Nothing! */
    }
}


void __attribute__((interrupt("ABORT"))) prefetch_abort_vector(void)
{

}

void __attribute__((interrupt("ABORT"))) data_abort_vector(void)
{

}