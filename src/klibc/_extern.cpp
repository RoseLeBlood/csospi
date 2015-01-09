#include <cxx/iostream.hpp>

#include <time.h>
#include <iob.h>
#include <kernel/kernel.hpp>
#include <dev/SysTimer.hpp>
extern "C" void* kernel_instance;


extern "C" uint32_t end;

#define SEC  1000000
extern "C" int	 GetDeviceByNameEx(char* name, void** device)
{
	*device = GetDeviceByName(name);
	return *device != NULL;
}
extern "C" void* GetDeviceByName(char* name)
{
	return ((Kernel*)kernel_instance)->GetDriver(name);	
}
extern "C" bool CPUID_IsSupport(uint32_t ext)
{
	return false;
}

/*extern "C" void sleep(int sec)
{
	dev::SysTimer* RandDevice = (dev::SysTimer*)GetDeviceByName("stmr0");
    if(RandDevice != NULL)
    {
    	RandDevice->Sleep(sec);
    }
}*/
extern "C" void gotoxy(int x, int y)
{
    std::cout.gotoxy(x,y);
}
extern "C" void putchar	(const char c)
{
	std::cout << c;
	
}
extern "C" void puts(const char *c)
{
	std::cout << c;
}
extern "C" void cls()
{
	std::cout.Clear();
}
extern "C" void setBackColor(uint8_t back)
{
	std::cout << (std::backcolor::backcolor_t)(back);
}
extern "C" void setFrontColor(uint8_t front)
{
	std::cout << (std::textcolor::textcolor_t)(front);
}
extern "C" int getch()
{       
    return std::cin.getChar();
}

extern "C" int SetTextColorStream(void* stream, uint16_t color);
extern "C" int SetBackColorStream(void* stream, uint16_t color);
extern "C" int WriteStream(void* stream, uint8_t* data, uint64_t offset, uint64_t size)
{
	IStream *str = (IStream*)stream;
	if(str != NULL)
		return (int)str->Write(data, offset, size);
	return 0;
}
extern "C" void WriteByteStream(void* stream, uint8_t byte)
{
	IStream *str = (IStream*)stream; //WriteChar
	if(str != NULL)
		str->WriteChar(byte);
}
extern "C" int ReadStream(void* stream, uint8_t* data, uint64_t offset, uint64_t size)
{
	IStream *str = (IStream*)stream;
	if(str != NULL)
		return (int)str->Read(data, offset, size);
	return 0;
}
extern "C" int ReadCharStream(void* stream)
{
	IStream *str = (IStream*)stream;
	if(str != NULL)
		return (int)str->ReadChar();
	return 0;
}
extern "C" int WriteCharStream(void* stream, uint8_t data)
{
	IStream *str = (IStream*)stream;
	if(str != NULL)
		str->WriteChar(data);
	return 0;
}
extern "C" int SeekStream(void* stream, uint64_t off, int8_t org)
{
	IStream *str = (IStream*)stream;
	if(str != NULL)
		return (int)str->Seek(off, (SeekOrigin::SeekOrigin_t)org);
	return 0;
}
extern "C" int CanReadStream(void* stream)
{
	IStream *str = (IStream*)stream;
	if(str != NULL)
		return (int)str->CanRead();
	return 0;
}
extern "C" int CanSeekStream(void* stream)
{	
	IStream *str = (IStream*)stream;
	if(str != NULL)
		return (int)str->CanSeek();

	return 0;
}
extern "C" int CanWriteStream(void* stream)
{
	IStream *str = (IStream*)stream;
	if(str != NULL)
		return (int)str->CanWrite();
	return 0;
}