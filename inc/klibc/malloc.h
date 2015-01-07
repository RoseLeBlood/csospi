
#ifndef KLIBC_MALLOC_H
#define KLIBC_MALLOC_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ctype.h"



void *malloc(size_t);
void **malloc2d(int, int, size_t);
void *calloc(size_t, size_t);
void *realloc(void *, size_t);
void free(void *);
void free2d(void** array, int, int);
#ifdef __cplusplus
};
#endif

#endif