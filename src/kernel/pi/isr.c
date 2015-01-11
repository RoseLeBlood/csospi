#include <kernel/isr.h>
#include <types.h>

#define  	INTERRUPT_REGS_BASE (0x2000B200)

#define BCM2835_NUM_GPU_SHARED_IRQS     64
#define BCM2835_NUM_ARM_SPECIFIC_IRQS   8

#define BCM2835_NUM_IRQS (BCM2835_NUM_GPU_SHARED_IRQS + BCM2835_NUM_ARM_SPECIFIC_IRQS)

interrupt_handler_t interruptVector[BCM2835_NUM_IRQS];

static uint32_t arm_enabled_irqs[3];



struct bcm2835_interrupt_registers 
{
    uint32_t IRQ_basic_pending;
    uint32_t IRQ_pending_1;
    uint32_t IRQ_pending_2;
    uint32_t FIQ_control;
    uint32_t Enable_IRQs_1;
    uint32_t Enable_IRQs_2;
    uint32_t Enable_Basic_IRQs;
    uint32_t Disable_IRQs_1;
    uint32_t Disable_IRQs_2;
    uint32_t Disable_Basic_IRQs;
};
static volatile struct bcm2835_interrupt_registers * const regs =
        (volatile struct bcm2835_interrupt_registers*)INTERRUPT_REGS_BASE;

static inline unsigned long first_set_bit(unsigned long word)
{
    return 31 - __builtin_clz(word);
}

void init_irq() 
{
   // enable_irq(BCM2835_IRQ_ID_TIMER_0);
	enable();
}
void enable_irq(unsigned long irq_num) 
{
	if (irq_num < 32)
    {
        regs->Enable_IRQs_1 = 1 << irq_num;
        arm_enabled_irqs[0] |= 1 << irq_num;
    }
    else if (irq_num < 64)
    {
        regs->Enable_IRQs_2 = 1 << (irq_num - 32);
        arm_enabled_irqs[1] |= 1 << (irq_num - 32);
    }
    else
    {
        regs->Enable_Basic_IRQs = 1 << (irq_num - 64);
        arm_enabled_irqs[2] |= 1 << (irq_num - 64);
    }
}

void disable_irq(unsigned long irq_num) 
{
    if (irq_num < 32)
    {
        regs->Disable_IRQs_1 = 1 << irq_num;
        arm_enabled_irqs[0] &= ~(1 << irq_num);
    }
    else if (irq_num < 64)
    {
        regs->Disable_IRQs_2 = 1 << (irq_num - 32);
        arm_enabled_irqs[1] &= ~(1 << (irq_num - 32));
    }
    else
    {
        regs->Disable_Basic_IRQs = 1 << (irq_num - 64);
        arm_enabled_irqs[2] &= ~(1 << (irq_num - 64));
    }
}
 





static void handle_irq(unsigned char irq_num)
{
    interrupt_handler_t handler = interruptVector[irq_num];
    if (handler)
    {
        (*handler)();
    }
    else
    {
        printf("ERROR: No handler registered for interrupt %u\r\n", irq_num);

        extern void halt(void);
        halt();
    }
}
static void check_irq_pending(unsigned char irq_num)
{
    bool handle = false;
 
    if (irq_num >= 64)
    {
        if (regs->IRQ_basic_pending & (1 << (irq_num - 64)))
        {
            handle = true;
        }
    }
    else if (irq_num >= 32)
    {
        if (regs->IRQ_pending_2 & (1 << (irq_num - 32)))
        {
            handle = true;
        }
    }
    else
    {
        if (regs->IRQ_pending_1 & (1 << irq_num))
        {
            handle = true;
        }
    }
    if (handle)
    {
        handle_irq(irq_num);
    }
}
extern void dispatch(void)
{
    printf("Jallo");

    uint32_t i;
  
    for (i = 0; i < 3; i++)
    {
        uint32_t mask = arm_enabled_irqs[i];
        while (mask != 0)
        {
            uint32_t bit = first_set_bit(mask);
            mask ^= (1 << bit);
            check_irq_pending(bit + (i << 5));
        }
    }
}