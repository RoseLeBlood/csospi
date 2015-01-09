#include <kernel/mailbox.h>
#include <types.h>

#define ATAG_NONE        0x00000000
#define ATAG_CORE        0x54410001
#define ATAG_MEM         0x54410002
#define ATAG_VIDEOTEXT   0x54410003
#define ATAG_RAMDISK     0x54410004
#define ATAG_INITRD2     0x54410005
#define ATAG_SERIAL      0x54410006
#define ATAG_REVISION    0x54410007
#define ATAG_VIDEOLFB    0x54410008
#define ATAG_CMDLINE     0x54410009


struct atag_header {
    uint32_t size;  /* Size of tag, in words, including the header.  */
    uint32_t tag;   /* One of the ATAG_* values from above.          */
};

struct atag_mem {
    uint32_t size;
    uint32_t start;
};

struct atag_serialnr {
    uint32_t low;
    uint32_t high;
};

struct atag {
    struct atag_header hdr;
    union {
        struct atag_mem mem;
        struct atag_serialnr serialnr;
    };
};

const struct atag *atags_ptr = (void*)-1;

extern void *end;

static void parse_platform_atag(void)
{
    const struct atag *atag;
    bool parse_again;
    uint64_t maxaddr = 0;

    do
    {
        parse_again = false;
        for (atag = atags_ptr;
             atag->hdr.size > 2 && atag->hdr.tag != ATAG_NONE;
             atag = (const struct atag*)((const uint32_t*)atag + atag->hdr.size))
        {
            switch (atag->hdr.tag)
            {
                case ATAG_MEM:
                    if (maxaddr == atag->mem.start && atag->mem.size != 0)
                    {
                        maxaddr += atag->mem.size;
                        parse_again = true;
                    }
                    break;
                case ATAG_SERIAL:
                    //platform.serial_low = atag->serialnr.low;
                    //platform.serial_high = atag->serialnr.high;
                    break;
                default:
                    break;
            }
        }
    } while (parse_again);

    /* Set platform maximum address if calculated value is not insane.  */
    if (maxaddr >= (uint64_t)&end)
    {
       // platform.maxaddr = (void*)maxaddr;
    }
}
void platforminit(void)
{
    parse_platform_atag();
}