#include <dev/serial_out.hpp>
#include <iob.h>
#include <kernel/video.h>
#include <stdio.h>
#include <cxx/iostream.hpp>
#include <kernel/put.h>
#include <config.h>

using namespace dev;
SerialOut::SerialOut(int port) : Driver("uart i/o", "uart", 0,0,0x07, true, true), m_port(port)
{ 
	//sprintf(m_Name, "%s ( 0x%X : %d )", m_Name, port, m_irq);
}

bool SerialOut::Probe()
{
	// Disable UART0.
	outi(GPIO::UART0_CR, 0x00000000);
	// Setup the GPIO pin 14 && 15.
 
	// Disable pull up/down for all GPIO pins & delay for 150 cycles.
	outi(GPIO::GPPUD, 0x00000000);
	iodelay(150);
 
	// Disable pull up/down for pin 14,15 & delay for 150 cycles.
	outi(GPIO::GPPUDCLK0, (1 << 14) | (1 << 15));
	iodelay(150);
 
	// Write 0 to GPPUDCLK0 to make it take effect.
	outi(GPIO::GPPUDCLK0, 0x00000000);
 
	// Clear pending interrupts.
	outi(GPIO::UART0_ICR, 0x7FF);
 
	// Set integer & fractional part of baud rate.
	// Divider = UART_CLOCK/(16 * Baud)
	// Fraction part register = (Fractional part * 64) + 0.5
	// UART_CLOCK = 3000000; Baud = 115200.
 
	uint32_t Divider = (uint32_t)(3000000 / (16 * UART0_BAUD)); // 1
	uint32_t Fractional  = (uint32_t)((.627 * 64) + 0.5); // 40.

	outi(GPIO::UART0_IBRD, Divider);
	outi(GPIO::UART0_FBRD, Fractional);
 
	// Enable FIFO & 8 bit data transmissio (1 stop bit, no parity).
	outi(GPIO::UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));
 
	// Mask all interrupts.
	outi(GPIO::UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
	                       (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));
 
	// Enable UART0, receive & transfer part of UART.
	outi(GPIO::UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));


	return true;
	
}
void SerialOut::callback(uint32_t irq)
{

	printf("UART");
}

char SerialOut::ReadChar()
{
	// wait for UART to have recieved something
	while(true) 
	{
	    if (!(ini(GPIO::UART0_FR) & (1 << 4))) 
	    {
			break;
	    }
	}
	char ch = ini(GPIO::UART0_DR);
	if(!ch) ch = ReadChar();
	return ch;
}
void SerialOut::WriteChar(char c)
{

	while ( ini(GPIO::UART0_FR) & (1 << 5) ) { }
	outi(GPIO::UART0_DR, c);

	if (c == '\n')
    {
        WriteChar('\r');

    }
}
void SerialOut::Write(const char* c)
{	
	startColor();
	const char *str = c, *ch;

	for(ch = str; *ch; ch ++) 
	{
		if(ch) WriteChar(*ch);
	}
	endColor();
}
void SerialOut::InternalWrite(const char* c)
{
	const char *str = c, *ch;

	for(ch = str; *ch; ch ++) 
	{
		if(ch) WriteChar(*ch);
	}
	//delete[] str;
}
void SerialOut::GotoXY(unsigned short x, unsigned short y)
{

}
void SerialOut::Clear()
{
	InternalWrite("\\033c"); 
}

void SerialOut::TextColor(uint16_t color)
{
	m_color = color;
}
void SerialOut::BackColor(uint16_t color)
{
	m_bcolor = color;
}	

uint64_t SerialOut::Read(uint8_t *data, uint64_t offset, uint64_t size)
{
		for(uint64_t i = 0; i < size; i++)
		{
			data[i] = ReadChar();
		}
		return size;
}
uint64_t SerialOut::Write(uint8_t *data, uint64_t offset, uint64_t size)
{
	unsigned char *str = data;
	for(uint64_t i= 0; i < size; i++)
	{
		WriteChar(str[i]);
	}
	
	return size;
}
bool SerialOut::readyToTransmit()
{

}
void SerialOut::startColor()
{
	InternalWrite("\\e[");

	switch(m_color)
	{
		case CGA_COLOR_BLACK: 	 InternalWrite("0;30"); break;
		case CGA_COLOR_RED:  	 InternalWrite("0;31"); break;
		case CGA_COLOR_GREEN: 	 InternalWrite("0;32"); break;
		case CGA_COLOR_BROWN:	 InternalWrite("0;33"); break;
		case CGA_COLOR_BLUE:  	 InternalWrite("0;34"); break;
		case CGA_COLOR_MAGENTA:  InternalWrite("0;35"); break;
		case CGA_COLOR_CYAN: 	 InternalWrite("0;36"); break;
		case CGA_COLOR_LGREY:	 InternalWrite("0;37"); break;
		
		case CGA_COLOR_DGREY:	 InternalWrite("1;30"); break;
		case CGA_COLOR_PINK: 	 InternalWrite("1;31"); break;
		case CGA_COLOR_LGREEN:   InternalWrite("1;32"); break;
		case CGA_COLOR_YELLOW:   InternalWrite("1;33"); break;
		case CGA_COLOR_LBLUE:    InternalWrite("1;34"); break;
		case CGA_COLOR_LMAGENTA: InternalWrite("1;35"); break;
		case CGA_COLOR_LCYAN: 	 InternalWrite("1;36"); break;
		case CGA_COLOR_WHITE: 	 InternalWrite("1;37"); break;

		default: InternalWrite("1");
	};
 
	switch(m_bcolor)
	{
		case CGA_COLOR_BLACK: 	 InternalWrite("0;40"); break;
		case CGA_COLOR_RED:  	 InternalWrite("0;41"); break;
		case CGA_COLOR_GREEN: 	 InternalWrite("0;42"); break;
		case CGA_COLOR_BROWN:	 InternalWrite("0;43"); break;
		case CGA_COLOR_BLUE:  	 InternalWrite("0;44"); break;
		case CGA_COLOR_MAGENTA:  InternalWrite("0;45"); break;
		case CGA_COLOR_CYAN: 	 InternalWrite("0;46"); break;
		case CGA_COLOR_LGREY:	 InternalWrite("0;47"); break;

		case CGA_COLOR_DGREY:	 InternalWrite("1;40"); break;
		case CGA_COLOR_PINK: 	 InternalWrite("1;41"); break;
		case CGA_COLOR_LGREEN:   InternalWrite("1;42"); break;
		case CGA_COLOR_YELLOW:   InternalWrite("1;43"); break;
		case CGA_COLOR_LBLUE:    InternalWrite("1;44"); break;
		case CGA_COLOR_LMAGENTA: InternalWrite("1;45"); break;
		case CGA_COLOR_LCYAN: 	 InternalWrite("1;46"); break;
		case CGA_COLOR_WHITE: 	 InternalWrite("1;47"); break;
	}
  	InternalWrite("m");
}
void SerialOut::endColor()
{
	InternalWrite("\\e[0m");
}