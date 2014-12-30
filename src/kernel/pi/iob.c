#include <iob.h>


unsigned char enabled;

void 			outi(uint32_t reg, uint32_t data)
{
	uint32_t *ptr = (uint32_t*) reg;
	asm volatile("str %[data], [%[reg]]" : : [reg]"r"(ptr), [data]"r"(data));
}
uint32_t		ini(uint32_t reg)
{
	uint32_t *ptr = (uint32_t*)reg;
	uint32_t data;
	asm volatile("ldr %[data], [%[reg]]" : [data]"=r"(data) : [reg]"r"(ptr));
	return data;
}
void outb( unsigned short port, unsigned char data )
{
    outi(port, data);
}
DWORD farpeekl( WORD sel, void * off )
{
   
}
void farpokeb( WORD sel, void *off, BYTE v )
{
    
}
unsigned char inb( unsigned short port )
{
	return ini(port);
}
void io_wait( void )
{
   iodelay(150);
}
void disable()
{

}
void halt()
{

}


unsigned short inw(unsigned short port)
{
	return 0;
}
void outw(unsigned short port, unsigned short data)
{

}
unsigned int inl(unsigned short port)
{
	return( port );
}
void outl(unsigned short port, unsigned int data)
{

}
void insb(unsigned short port, unsigned char *data, unsigned int count)
{
	for(;count !=0;count--)
	{
		*data = inb(port);
		data++;
	}
}
void insw(short port, unsigned short *data, unsigned count)
{
	for(; count != 0; count--)
	{
		*data = inw(port);
		data++;
	}
}
void insdw(unsigned short port, unsigned int *data, unsigned int count)
{
	for(; count != 0; count--)
	{
		*data = inl(port);
		data++;
	}
}
void outsb(unsigned short port, unsigned char *data, unsigned int count)
{
	for(; count != 0; count--)
	{
		outb(port, *data);
		data++;
	}
}
void outsw(short port, unsigned short *data, unsigned count)
{
	for(; count != 0; count--)
	{
		outw(port, *data);
		data++;
	}
}
void outsdw(unsigned short port, unsigned int *data, unsigned int count)
{
	for(; count != 0; count--)
	{
		outl(port, *data);
		data++;
	}
}
void iodelay(int count)
{ 
	asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
	 : : [count]"r"(count) : "cc");

}
void 			outd(uint16_t port, uint32_t value)
{
	outi(port, value);
}
uint32_t 		ind(uint16_t port)
{
	return ini(port); 
}
	
	
	
	

