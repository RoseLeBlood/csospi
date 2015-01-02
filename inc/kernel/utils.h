#ifndef MAIN_UTILS_H
#define MAIN_UTILS_H

#include <types.h>
#include <config.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define BCM2835_MBOX_PHYSADDR				0x2000b880
#define BCM2835_MBOX_TAG_GET_CLOCK_RATE		0x00030002
#define BCM2835_MBOX_CLOCK_ID_EMMC			1
#define BCM2835_MBOX_STATUS_WR_FULL			0x80000000
#define BCM2835_MBOX_STATUS_RD_EMPTY		0x40000000
#define BCM2835_MBOX_PROP_CHAN				8
#define BCM2835_MBOX_TAG_VAL_LEN_RESPONSE	0x80000000

#define FBFAIL_GET_RESOLUTION			1
#define FBFAIL_GOT_INVALID_RESOLUTION	2
#define FBFAIL_SETUP_FRAMEBUFFER		3
#define FBFAIL_INVALID_TAGS				4
#define FBFAIL_INVALID_TAG_RESPONSE		5
#define FBFAIL_INVALID_TAG_DATA			6
#define FBFAIL_INVALID_PITCH_RESPONSE	7
#define FBFAIL_INVALID_PITCH_DATA		8



struct KernelFrameBuffer
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


int get_cpu_freq(void);
int get_system_mem();
int get_video_mem();

struct KernelFrameBuffer* 	get_framebuffer_info();
bool						set_framebuffer(struct KernelFrameBuffer* fb);



#ifdef __cplusplus
}
#endif

#endif