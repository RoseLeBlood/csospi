#ifndef __DEV_ARM_TIMER_HPP__
#define __DEV_ARM_TIMER_HPP__

#include <dev/Driver.hpp>
#include <iob.h>

#define RPI_ARMTIMER_BASE       0x2000B400


namespace dev
{
	struct rpi_arm_timer_t 
	{
		volatile uint32_t Load;
		volatile uint32_t Value;
		volatile uint32_t Control;
		volatile uint32_t IRQClear;
		volatile uint32_t RAWIRQ;
		volatile uint32_t MaskedIRQ;
		volatile uint32_t Reload;
		volatile uint32_t PreDivider;
		volatile uint32_t FreeRunningCounter;
    } ;

	class ArmTimer : public Driver
	{
	public:
		ArmTimer() ;

		virtual bool Probe();

		virtual register_t* callback(register_t* state);
	private:
		rpi_arm_timer_t* m_rpiArmTimer;
		uint32_t		 m_ticks;
	};
}
#endif
