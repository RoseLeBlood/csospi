#include <kernel/utils.h>
#include <kernel/mailbox.h>
#include <stdio.h>
#include <string.h>
#include <mmalloc.h>
#include <kernel/pmm.h>
#include <config.h>

extern void *end;

int get_cpu_freq(void)
{
	int alignedEnd = (unsigned int)&end;
	alignedEnd+=15;
	alignedEnd&=~15;
	
	volatile unsigned int *ptr = (unsigned int *)alignedEnd;
	memset((void*)ptr, '\0', 13);
	
	unsigned int var;

	ptr[0] = 13 * 4;	// Total size
	ptr[1] = 0;		// Request

	ptr[2] = BCM2835_MBOX_TAG_GET_CLOCK_RATE;
	ptr[3] = 8;				// Buffer size
	ptr[4] = 4;				// Request size
	ptr[5] = BCM2835_MBOX_CLOCK_ID_ARM;
	ptr[6] = 0;

	bcm_write_mailbox(BCM2835_MBOX_CHANNEL_PROPERTY, (unsigned int)ptr);

	var = bcm_read_mailbox(BCM2835_MBOX_CHANNEL_PROPERTY);

	return (ptr[6] / 1000 / 1000);
}
int get_system_mem()
{
	int alignedEnd = (unsigned int)&end;
	alignedEnd+=15;
	alignedEnd&=~15;
	
	volatile unsigned int *ptr = (unsigned int *)alignedEnd;
	unsigned int var;

	ptr[0] = 13 * 4;	// Total size
	ptr[1] = 0;		// Request

	ptr[2] = BCM2835_MBOX_TAG_GET_ARM_MEMORY;	// ARM memory
	ptr[3] = 8;		// Buffer size
	ptr[4] = 0;		// Request size
	ptr[5] = 0;
	ptr[6] = 0;

	bcm_write_mailbox(BCM2835_MBOX_CHANNEL_PROPERTY, (unsigned int)ptr);

	var = bcm_read_mailbox(BCM2835_MBOX_CHANNEL_PROPERTY);

	return ptr[6];
}
int get_video_mem()
{
	int alignedEnd = (unsigned int)&end;
	alignedEnd+=15;
	alignedEnd&=~15;
	
	volatile unsigned int *ptr = (unsigned int *)alignedEnd;
	unsigned int var;

	ptr[0] = 13 * 4;	// Total size
	ptr[1] = 0;		// Request

	ptr[2] = BCM2835_MBOX_TAG_GET_GPU_MEMORY;	// GPU memory
	ptr[3] = 8;		// Buffer size
	ptr[4] = 0;		// Request size
	ptr[5] = 0;
	ptr[6] = 0;

	bcm_write_mailbox(BCM2835_MBOX_CHANNEL_PROPERTY, (unsigned int)ptr);

	var = bcm_read_mailbox(BCM2835_MBOX_CHANNEL_PROPERTY);

	return ptr[6];
}
static bool fb_fail(unsigned int num)
{
	return false;
}

struct FrameBuffer* get_framebuffer_info()
{
	struct FrameBuffer *__mpBuffer_frame__ = (struct FrameBuffer*)malloc(sizeof(struct FrameBuffer));

	unsigned int var;
	unsigned int count;
	volatile unsigned int *mailbuffer = (unsigned int *)_mm_malloc(16, 32);

	/* Get the display size */
	mailbuffer[0] = 8 * 4;		// Total size
	mailbuffer[1] = 0;		// Request
	mailbuffer[2] = BCM2835_MBOX_TAG_GET_PHYSICAL_W_H;	// Display size
	mailbuffer[3] = 8;		// Buffer size
	mailbuffer[4] = 0;		// Request size
	mailbuffer[5] = 0;		// Space for horizontal resolution
	mailbuffer[6] = 0;		// Space for vertical resolution
	mailbuffer[7] = 0;		// End tag

	bcm_write_mailbox(BCM2835_MBOX_CHANNEL_PROPERTY, (unsigned int)mailbuffer);

	var = bcm_read_mailbox(BCM2835_MBOX_CHANNEL_PROPERTY);
	if(mailbuffer[1] != BCM2835_MBOX_RESP_CODE_SUCCESS)
		fb_fail(FBFAIL_GET_RESOLUTION);	

	__mpBuffer_frame__->ifbX = mailbuffer[5];
	__mpBuffer_frame__->ifbY = mailbuffer[6];

	if(__mpBuffer_frame__->ifbX==0 || __mpBuffer_frame__->ifbY==0)
		fb_fail(FBFAIL_GOT_INVALID_RESOLUTION);
	
	__mpBuffer_frame__->iFontMaxX = __mpBuffer_frame__->ifbX / CHARSIZE_X;
	__mpBuffer_frame__->iFontMaxY = __mpBuffer_frame__->ifbY / CHARSIZE_Y;
	__mpBuffer_frame__->iDepth = FRMEBUFFER_DEPTH;

	return __mpBuffer_frame__;
}
bool set_framebuffer(struct FrameBuffer* fb)
{
	unsigned int var;
	unsigned int count;
	volatile unsigned int *mailbuffer = (unsigned int *)_mm_malloc(16, 32);

	mailbuffer[0] = 22*4;		// Buffer size

	mailbuffer[1] = 0;		// Request

	mailbuffer[2] = BCM2835_MBOX_TAG_SET_PHYSICAL_W_H;	// Tag id (set physical size)
	mailbuffer[3] = 8;		// Value buffer size (bytes)
	mailbuffer[4] = 8;		// Req. + value length (bytes)
	mailbuffer[5] = fb->ifbX;		// Horizontal resolution
	mailbuffer[6] = fb->ifbY;		// Vertical resolution

	mailbuffer[7] = BCM2835_MBOX_TAG_SET_VIRTUAL_W_H;	// Tag id (set virtual size)
	mailbuffer[8] = 8;		// Value buffer size (bytes)
	mailbuffer[9] = 8;		// Req. + value length (bytes)
	mailbuffer[10] = fb->ifbX;		// Horizontal resolution
	mailbuffer[11] = fb->ifbY;		// Vertical resolution

	mailbuffer[12] = BCM2835_MBOX_TAG_SET_DEPTH;	// Tag id (set depth)
	mailbuffer[13] = 4;		// Value buffer size (bytes)
	mailbuffer[14] = 4;		// Req. + value length (bytes)
	mailbuffer[15] = fb->iDepth;	// X bpp

	mailbuffer[16] = BCM2835_MBOX_TAG_ALLOCATE_BUFFER;	// Tag id (allocate framebuffer)
	mailbuffer[17] = 8;		// Value buffer size (bytes)
	mailbuffer[18] = 4;		// Req. + value length (bytes)
	mailbuffer[19] = 16;		// Alignment = 16
	mailbuffer[20] = 0;		// Space for response

	mailbuffer[21] = 0;		// Terminating tag

	bcm_write_mailbox(BCM2835_MBOX_CHANNEL_PROPERTY, (unsigned int)mailbuffer);

	var = bcm_read_mailbox(BCM2835_MBOX_CHANNEL_PROPERTY);

	/* Valid response in data structure */
	if(mailbuffer[1] != BCM2835_MBOX_RESP_CODE_SUCCESS)
		return fb_fail(FBFAIL_SETUP_FRAMEBUFFER);	

	count=2;	/* First tag */
	while((var = mailbuffer[count]))
	{
		if(var == BCM2835_MBOX_TAG_ALLOCATE_BUFFER)
			break;

		/* Skip to next tag
		 * Advance count by 1 (tag) + 2 (buffer size/value size)
		 *                          + specified buffer size
		*/
		count += 3+(mailbuffer[count+1]>>2);

		if(count > 22)
			fb_fail(FBFAIL_INVALID_TAGS);
	}

	/* 8 bytes, plus MSB set to indicate a response */
	if(mailbuffer[count+2] != 0x80000008)
		return fb_fail(FBFAIL_INVALID_TAG_RESPONSE);

	/* Framebuffer address/size in response */
	fb->iBaseAdress =  mailbuffer[count+3];
	fb->iSize = mailbuffer[count+4];

	fb->pFramebuffer = pmm_reserve_addr(fb->iSize, (void*)fb->iBaseAdress);

	if(fb->iBaseAdress == 0 || fb->iSize == 0)
		return fb_fail(FBFAIL_INVALID_TAG_DATA);

	/* Get the framebuffer pitch (bytes per line) */
	mailbuffer[0] = 7 * 4;		// Total size
	mailbuffer[1] = 0;		// Request
	mailbuffer[2] = BCM2835_MBOX_TAG_GET_PITCH;	// Display size
	mailbuffer[3] = 4;		// Buffer size
	mailbuffer[4] = 0;		// Request size
	mailbuffer[5] = 0;		// Space for pitch
	mailbuffer[6] = 0;		// End tag

	bcm_write_mailbox(BCM2835_MBOX_CHANNEL_PROPERTY, (unsigned int)mailbuffer);

	var = bcm_read_mailbox(BCM2835_MBOX_CHANNEL_PROPERTY);

	/* 4 bytes, plus MSB set to indicate a response */
	if(mailbuffer[4] != 0x80000004)
		return fb_fail(FBFAIL_INVALID_PITCH_RESPONSE);

	fb->iPitch = mailbuffer[5];
	if(fb->iPitch == 0)
		return fb_fail(FBFAIL_INVALID_PITCH_DATA);

	return true;
}