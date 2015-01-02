#ifndef __DEV_SERIAL_OUT_HPP__
#define __DEV_SERIAL_OUT_HPP__

#include <dev/Driver.hpp>
#include <iob.h>

namespace dev
{
	namespace GPIO
	{
		enum GPIO_T
		{
		    // The GPIO registers base address.
		    BASE = 0x20200000,
		 
		    // The offsets for reach register.
		 
		    // Controls actuation of pull up/down to ALL GPIO pins.
		    GPPUD = (BASE + 0x94),
		 
		    // Controls actuation of pull up/down for specific GPIO pin.
		    GPPUDCLK0 = (BASE + 0x98),
		 
		    // The base address for UART.
		    UART0_BASE = 0x20201000,
		 
		    // The offsets for reach register for the UART.
		    UART0_DR     = (UART0_BASE + 0x00),
		    UART0_RSRECR = (UART0_BASE + 0x04),
		    UART0_FR     = (UART0_BASE + 0x18),
		    UART0_ILPR   = (UART0_BASE + 0x20),
		    UART0_IBRD   = (UART0_BASE + 0x24),
		    UART0_FBRD   = (UART0_BASE + 0x28),
		    UART0_LCRH   = (UART0_BASE + 0x2C),
		    UART0_CR     = (UART0_BASE + 0x30),
		    UART0_IFLS   = (UART0_BASE + 0x34),
		    UART0_IMSC   = (UART0_BASE + 0x38),
		    UART0_RIS    = (UART0_BASE + 0x3C),
		    UART0_MIS    = (UART0_BASE + 0x40),
		    UART0_ICR    = (UART0_BASE + 0x44),
		    UART0_DMACR  = (UART0_BASE + 0x48),
		    UART0_ITCR   = (UART0_BASE + 0x80),
		    UART0_ITIP   = (UART0_BASE + 0x84),
		    UART0_ITOP   = (UART0_BASE + 0x88),
		    UART0_TDR    = (UART0_BASE + 0x8C),
		};
	}

	class SerialOut : public Driver
	{
	public:
		SerialOut(int port) ;

		virtual bool Probe();
		
		virtual char ReadChar();
		virtual void WriteChar(char c);
		virtual void Write(const char* c);
		virtual void GotoXY(unsigned short x, unsigned short y);
		virtual void Clear();
		
		virtual void TextColor(uint16_t color);
		virtual void BackColor(uint16_t color);
		
		virtual uint64_t Read(uint8_t *data, uint64_t offset, uint64_t size);
		virtual uint64_t Write(uint8_t *data, uint64_t offset, uint64_t size);
		register_t* callback(register_t* state);

		int getPort() { return m_port; }
	protected:
		bool readyToTransmit();
		
		void startColor();
		void endColor();
	private:
		void InternalWrite(const char* c);
	protected:
		int m_port;
		int m_irq;
		uint16_t m_bcolor;
	};
}
#endif
