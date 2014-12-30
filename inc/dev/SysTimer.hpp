#ifndef __DEV_RPI_TIMER_HPP__
#define __DEV_RPI_TIMER_HPP__

#include <dev/Driver.hpp>
#include <iob.h>

#define RPI_SYSTIMER_BASE       0x20003000

namespace dev
{
	struct rpi_sys_timer_t
	{
		volatile uint32_t control_status;
		volatile uint32_t counter_lo;
		volatile uint32_t counter_hi;
		volatile uint32_t compare0;
		volatile uint32_t compare1;
		volatile uint32_t compare2;
		volatile uint32_t compare3;
	} ;
	class SysTimer : public Driver
	{
	public:
		SysTimer() ;

		virtual bool Probe();
		virtual int Sleep(uint32_t us );
		//virtual char ReadChar();
		//virtual uint64_t Read(uint8_t *data, uint64_t offset, uint64_t size);
	private:
		rpi_sys_timer_t* m_rpiSystemTimer;
	};
}
#endif