#ifndef MAIN_POWER_H
#define MAIN_POWER_H

#include <types.h>
#include <config.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define POWER_SD      0
#define POWER_UART_0  1
#define POWER_UART_1  2
#define POWER_USB     3

bool setpower(uint32_t feature, bool on);
void power_init();

#ifdef __cplusplus
}
#endif

#endif