#ifndef MAIN_MAILBOX_H
#define MAIN_MAILBOX_H

#ifdef __cplusplus
extern "C"
{
#endif

#define BCM2835_MBOX_CHANNEL_POWER    0 /* for use by the power management interface */
#define BCM2835_MBOX_CHANNEL_FB       1 /* for use by the frame buffer */
#define BCM2835_MBOX_CHANNEL_VCHIQ    3 /* for use by the VCHIQ interface */
#define BCM2835_MBOX_CHANNEL_PROPERTY 8 /* for use by the property channel */
#define BCM2835_MBOX_CHANNEL_COUNT    9

#define BCM2835_MBOX_STATUS_RD_EMPTY	0x40000000
#define BCM2835_MBOX_STATUS_WR_FULL	0x80000000

#define BCM2835_MBOX_RESP_CODE_SUCCESS	0x80000000

#define BCM2835_MBOX_TAG_GET_ARM_MEMORY		0x00010005
#define BCM2835_MBOX_TAG_GET_GPU_MEMORY		0x00010006

#define BCM2835_MBOX_TAG_GET_CLOCK_RATE        0x00030002

#define BCM2835_MBOX_TAG_ALLOCATE_BUFFER	0x00040001
#define BCM2835_MBOX_TAG_GET_PHYSICAL_W_H	0x00040003
#define BCM2835_MBOX_TAG_GET_PITCH		0x00040008

#define BCM2835_MBOX_TAG_SET_PHYSICAL_W_H	0x00048003
#define BCM2835_MBOX_TAG_SET_VIRTUAL_W_H	0x00048004
#define BCM2835_MBOX_TAG_SET_DEPTH		0x00048005

#define BCM2835_MBOX_CLOCK_ID_ARM      3
#define BCM2835_MBOX_CLOCK_ID_CORE     4



unsigned int bcm_read_mailbox(unsigned int channel);
void 		 bcm_write_mailbox(unsigned int channel, unsigned int data);




#ifdef __cplusplus
}
#endif

#endif