#include <sleep.h>

void udelay(uint32_t usec)
{
	unsigned nloops = (usec * (SYS_CLK_KHZ / 1000) + 7) >> 3;

        do {
                asm volatile ("nop");
                asm volatile ("nop");
                asm volatile ("nop");
                asm volatile ("nop");
        } while (--nloops);
}
void mdelay (unsigned msec)
{
        while (msec-- > 0) {
                udelay (1000);
        }
}
