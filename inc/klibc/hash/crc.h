#ifndef	_HASH_CRC_H
#define	_HASH_CRC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <types.h>

uint16_t* crc16s(const char* data, size_t lenght, char* hash);
uint32_t* crc32(const char* data, size_t lenght, char* hash);

#ifdef	__cplusplus
}
#endif

#endif	
