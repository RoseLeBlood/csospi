#ifndef MAIN_POWER_H
#define MAIN_POWER_H

#include <types.h>
#include <config.h>

#ifdef __cplusplus
extern "C"
{
#endif

bool setpower(uint32_t feature, bool on);
void power_init();

#ifdef __cplusplus
}
#endif

#endif