#ifndef MAIN_ISR_H
#define MAIN_ISR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <ctype.h>

#define BCM2835_INTC_TOTAL_IRQ		64 + 8

#define BCM2835_IRQ_ID_AUX			29
#define BCM2835_IRQ_ID_SPI_SLAVE 	43
#define BCM2835_IRQ_ID_PWA0			45
#define BCM2835_IRQ_ID_PWA1		   	46
#define BCM2835_IRQ_ID_SMI 			48
#define BCM2835_IRQ_ID_GPIO_0 		49
#define BCM2835_IRQ_ID_GPIO_1 		50
#define BCM2835_IRQ_ID_GPIO_2 		51
#define BCM2835_IRQ_ID_GPIO_3 		52
#define BCM2835_IRQ_ID_I2C 			53
#define BCM2835_IRQ_ID_SPI 			54
#define BCM2835_IRQ_ID_PCM 			55
#define BCM2835_IRQ_ID_UART 		57


#define BCM2835_IRQ_ID_TIMER_0 		64
#define BCM2835_IRQ_ID_MAILBOX_0	65
#define BCM2835_IRQ_ID_DOORBELL_0 	66
#define BCM2835_IRQ_ID_DOORBELL_1 	67
#define BCM2835_IRQ_ID_GPU0_HALTED 	68




typedef void (*interrupt_handler_t)(uint32_t irq);

extern interrupt_handler_t interruptVector[];

typedef unsigned long irqmask;  /**< machine status for disable/restore  */

void 		  init_irq(); //
void   		  enable_irq(void); 
void		  disable_irq(void);
void 		  enable_irq_n(unsigned long); //
void 		  disable_irq_n(unsigned long); //

void		  set_handler(unsigned long irq, interrupt_handler_t handler, void* userdata);
#ifdef __cplusplus
}
#endif

#endif
