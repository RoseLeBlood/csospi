#include <types.h>
#include <kernel/power.h>

extern unsigned int     bcm_read_mailbox(unsigned int channel);
extern void 		    bcm_write_mailbox(unsigned int channel, unsigned int data);

#define MAILBOX_CHANNEL_POWER_MGMT 0

static uint32_t bcm_power_mask;

static uint32_t get_power_mask(void)
{
    return (bcm_read_mailbox(MAILBOX_CHANNEL_POWER_MGMT) >> 4);
}

/* Set the bitmask of power on/off state.  */
static void set_power_mask(uint32_t mask)
{
    bcm_write_mailbox(MAILBOX_CHANNEL_POWER_MGMT, mask << 4);
}

bool setpower(uint32_t feature, bool on)
{
    uint32_t bit;
    uint32_t newmask;
    bool is_on;

    bit = 1 << feature;
    is_on = (bcm_power_mask & bit) != 0;
    if (on != is_on)
    {
        newmask = bcm_power_mask ^ bit;
        set_power_mask(newmask);
        bcm_power_mask = get_power_mask();
        if (bcm_power_mask != newmask)
        {
            return false;
        }
    }
    return true;
}
void power_init(void)
{
    set_power_mask(0);
    bcm_power_mask = 0;
}
