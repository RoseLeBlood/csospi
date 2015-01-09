
#ifndef _STDC_SLEEP_H_
#define _STDC_SLEEP_H_

#include <types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SYS_CLK_MHZ    (3000)
#define SYS_CLK_KHZ    (SYS_CLK_MHZ * 1000)
#define SYS_CLK_HZ     (SYS_CLK_KHZ * 1000)

void udelay(uint32_t usec);
void mdelay (unsigned msec);

#define delay(sec)  mdelay((sec)*1000)


#ifdef __cplusplus
}
#endif


#endif
