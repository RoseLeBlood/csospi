#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifdef __cplusplus
extern "C" 
{
#endif

#include <types.h>

struct FrameBuffer
{
	uint32_t ifbX;
	uint32_t ifbY;
	uint32_t iDepth;
	uint32_t iPitch;
	uint32_t iFontMaxX;
	uint32_t iFontMaxY;
	uint32_t iBaseAdress;
	void*	 pFramebuffer;
	uint32_t 	iSize;
};



#ifdef __cplusplus
};
#endif

#endif