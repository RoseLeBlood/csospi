#include <dev/ArmTimer.hpp>
#include <iob.h>
#include <kernel/video.h>
#include <stdio.h>
#include <config.h>

/** @brief 0 : 16-bit counters - 1 : 23-bit counter */
#define RPI_ARMTIMER_CTRL_16BIT			0
#define RPI_ARMTIMER_CTRL_23BIT         ( 1 << 1 )

#define RPI_ARMTIMER_CTRL_PRESCALE_1    ( 0 << 2 )
#define RPI_ARMTIMER_CTRL_PRESCALE_16   ( 1 << 2 )
#define RPI_ARMTIMER_CTRL_PRESCALE_256  ( 2 << 2 )

/** @brief 0 : Timer interrupt disabled - 1 : Timer interrupt enabled */
#define RPI_ARMTIMER_CTRL_INT_ENABLE    ( 1 << 5 )
#define RPI_ARMTIMER_CTRL_INT_DISABLE   ( 0 << 5 )

/** @brief 0 : Timer disabled - 1 : Timer enabled */
#define RPI_ARMTIMER_CTRL_ENABLE        ( 1 << 7 )
#define RPI_ARMTIMER_CTRL_DISABLE       ( 0 << 7 )

using namespace dev;
ArmTimer::ArmTimer() : Driver("ArmTimer","tmr", true, false)
{
	m_ticks = 0;
}
bool ArmTimer::Probe()
{
	m_rpiArmTimer = (rpi_arm_timer_t*)RPI_ARMTIMER_BASE;

	/* Setup the system timer interrupt */
    /* Timer frequency = Clk/256 * 0x400 */
    m_rpiArmTimer->Load = 0x800;

    /* Setup the ARM Timer */
    m_rpiArmTimer->Control =
            RPI_ARMTIMER_CTRL_23BIT |
            RPI_ARMTIMER_CTRL_ENABLE |
            RPI_ARMTIMER_CTRL_INT_ENABLE |
            RPI_ARMTIMER_CTRL_PRESCALE_256;

    setHandler(BCM2835_IRQ_ID_TIMER_0);
	set_on_irq(BCM2835_IRQ_ID_TIMER_0);

	return m_rpiArmTimer != NULL;
}
register_t* ArmTimer::callback(register_t* state)
{
	/* Clear the ARM Timer interrupt - it's the only interrupt we have
       enabled, so we want don't have to work out which interrupt source
       caused us to interrupt */
    m_rpiArmTimer->IRQClear = 1;
	
	m_ticks++;


	printf("Ticks: %i\r", m_ticks);
}