#include <types.h>
#include <string.h>
#include <hash/utils.h>

uint32_t quersum(uint32_t iZahl)
{
	uint32_t iQuer = 0;

	while (iZahl > 0)
	{ 
		iQuer += iZahl % 10; 
		iZahl /= 10; 
	}
	return iQuer;
}
uint32_t querhash(const char* data, size_t lenght)
{
	uint32_t iQuer = 0;
	for(uint32_t i = 0; i < lenght; i++)
	{
		iQuer += quersum(data[i]);
	}
	return (iQuer);
}