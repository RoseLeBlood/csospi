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

struct register_t
{
    // r13 und r14 des Usermodes
    uint32_t usr_r13, usr_r14;
    // CPSR vor dem IRQ und SPSR des Supervisormodes
    uint32_t cpsr, svc_spsr;
    // r13 und r14 des Supervisormodes
    uint32_t svc_r13, svc_r14;
    // r0 bis r12 sowie r15
    uint32_t r0, r1, r2, r3, r4, r5, r6, r7;
    uint32_t r8, r9, r10, r11, r12, r15;
} __attribute__((packed));


typedef struct register_t* (*isr_t)(struct register_t*, void*);

int 	init_isr	();

int 	set_handler(uint8_t n, isr_t handler);
int 	set_handlerex(uint8_t n, isr_t handler, void* userdata);
int 	set_on_irq				(int n);
int 	set_off_irq				(int n);
int 	enable_irq				();
int 	disable_irq				();

#ifdef __cplusplus
}
#endif

#endif
