#include <kernel/isr.h>
#include <iob.h>

#include <stdio.h>

#define IC_REGS ((volatile uint32_t *)0x14000000)

struct isr_handler_struct
{
	isr_t interrupt_handlers;
	void* userdata;
};

struct isr_handler_struct  interrupt_handlers[32];



void set_handler(uint8_t n, isr_t handler)
{
	set_handlerex(n, handler, NULL);
}
void set_handlerex(uint8_t n, isr_t handler, void* userdata)
{
	interrupt_handlers[n].interrupt_handlers = handler;
    interrupt_handlers[n].userdata = userdata;

    IC_REGS[2] |= 1 << n;
}

struct register_t* __attribute__((interrupt("IRQ"))) isr_handle(struct register_t* state)
{
    unsigned irq = 0;
  
    // In diesem Register sind die Bits der IRQs gesetzt, aufgrund deren dieser
    // IRQ ausgelÃ¶st wurde; durch das Lesen werden alle Bits zurÃ¼ckgesetzt
   uint32_t status = IC_REGS[0];

    while (status)
    {
        if (status & 1)
        {
        	isr_t handler = interrupt_handlers[irq].interrupt_handlers;
        	handler(state, interrupt_handlers[irq].userdata);
        }

        irq++;
        status >>= 1;
    }


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