#ifndef	_HASH_MD5_H
#define	_HASH_MD5_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <types.h>
#include <stdio.h>
#include <string.h>

struct md5_buffer;

struct md5_buffer* md5_create_buffer(const char* data,size_t lenght);
struct md5_buffer* md5_do(struct md5_buffer* crx); 
void   md5_hash(struct md5_buffer* crx, char* ret);

void   md5(const char* text, char* hash);
#ifdef	__cplusplus
}
#endif

#endif	/* _HASH_MD5_H */