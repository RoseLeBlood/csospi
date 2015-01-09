#ifndef	_HASH_ADLER_H
#define	_HASH_ADLER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <types.h>
#include <stdio.h>
#include <string.h>

uint32_t adler32ex (uint32_t initial,const char* data, uint32_t start, size_t length);
uint32_t adler32 (uint32_t initial,const char* data, size_t length);

#ifdef	__cplusplus
}
#endif

#endif	
