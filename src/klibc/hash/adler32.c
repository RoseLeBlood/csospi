#include <hash/adler32.h>
#include <types.h>
#include <string.h>

#define BASE 65521
#define MAX  5552

uint32_t adler32ex (uint32_t initial,const char* data, uint32_t start, size_t length)
{
	uint32_t s1 = (uint32_t)(initial & 0xffff);
	uint32_t s2 = (uint32_t)((initial >> 16) & 0xffff);

	int index=start;
	int len = length;

	int k;
	while (len > 0)
	{
		k = (len < MAX) ? len : MAX;
		len -= k;

		for (uint32_t i=0; i < k; i++)
		{
			s1 += (uint32_t)(data[index++]);
			s2 += s1;
		}
		s1 %= BASE;
		s2 %= BASE;
	}

	return (int)((s2<<16) | s1);
}


uint32_t adler32 (uint32_t initial,const char* data, size_t length)
{
	if (data == NULL)
		return -1;
	size_t l = memlen(uint8_t, data);

	return adler32ex(initial, data, 0, length);
}