#include <dev/SysTimer.hpp>
#include <iob.h>
#include <kernel/video.h>
#include <stdio.h>

using namespace dev;
SysTimer::SysTimer() : Driver("Raspberry PI SysTimer","stmr", true, false)
{

}
bool SysTimer::Probe()
{
	m_rpiSystemTimer = (rpi_sys_timer_t*)RPI_SYSTIMER_BASE;
	return m_rpiSystemTimer != NULL;
}
int SysTimer::Sleep(uint32_t us )
{
	volatile uint32_t ts = m_rpiSystemTimer->counter_lo;

	while( ( m_rpiSystemTimer->counter_lo - ts ) < us )
	{
	    /* BLANK */
	}
}