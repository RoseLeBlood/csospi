#include <stdarg.h>
#include <stdint.h>
#include <kernel/put.h>
 
#define SERIAL_DR *((volatile uint8_t  *)0x16000000)
#define SERIAL_FR *((volatile uint32_t *)0x16000018)
#define SERIAL_BUFFER_FULL (1 << 5)

void kput(char c)
{
    // Warten, bis Daten gesendet werden können
    while (SERIAL_FR & SERIAL_BUFFER_FULL);
 
    // Nächstes Zeichen senden
    SERIAL_DR = c;
}


