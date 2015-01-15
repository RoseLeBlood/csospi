#include <dev/Framebuffer.hpp>
#include <kernel/kernel.hpp>
#include <kernel/video.h>

#include <malloc.h>
#include <string.h>
#include <kernel/utils.h>
#include <math.h>
#include <config.h>
#include <kernel/kernel.hpp>

using namespace dev;

extern "C" void* kernel_instance; //class Kernel

extern "C" unsigned char FONTNAME[128][FONT_INT];


bool Framebuffer::Probe()
{
	m_fb = Kernel::Instance().GetKernelFrambuffer();

	if(set_framebuffer(m_fb))
	{
		m_mem = (unsigned char *) m_fb->pFramebuffer;

		m_txtColor = 0xFFFFFF;
		m_backColor = 0x000000;
		Clear();
		return true;
	}

	return false;
}
void Framebuffer::Swap(unsigned char* buffer, uint32_t size)
{
	memcpy(m_mem, buffer, size);
}
void Framebuffer::put(char c)
{
	unsigned char *let_data;
	int x = xpos;
	int y = ypos;

	let_data = FONTNAME[(unsigned char)c];


	for(int i = 0; i < CHARSIZE_X; i++)
	{
		for(int j = 0; j < CHARSIZE_Y; j++)
		{	
			SetPixel(x+j, y+i-4, (((let_data[i] & (1 << j)) > 0) ? m_txtColor : m_backColor ) );
		}
	}

}
void Framebuffer::InternalWrite(char c)
	{
		int t = 0;
		switch(c)
		{
		case '\r':                         //-> carriage return
			xpos = CHARSIZE_X / 2;
			break;
		case '\n':                         // -> newline (with implicit cr) 
			xpos = CHARSIZE_X / 2;
			ypos += CHARSIZE_Y + 2;
			break;
		case '\t':
			xpos = (xpos + LIB_TAB_SIZE * CHARSIZE_X ) &  ~(LIB_TAB_SIZE * CHARSIZE_X - 1);
			break;
		case '\b':                            // -> backspace 
			
			if(xpos > 4)
			{
				xpos -= CHARSIZE_X;
			}
			else if(ypos > 4)
			{
				ypos -= CHARSIZE_X + 2;
				xpos = m_fb->ifbX - (CHARSIZE_Y + (CHARSIZE_X / 2));
			}
			put(' ');
			break;
		default:
			if(c < ' ') break;
			put(c);
			xpos += CHARSIZE_X;
			if(xpos >= m_fb->ifbX - CHARSIZE_X)
			{
				xpos = 4;
				ypos += (CHARSIZE_Y + 2);
			}
			break;
		}
		if(ypos >= m_fb->ifbY - CHARSIZE_Y)
		{
			Clear();
			ypos--;
		}
}
void Framebuffer::Clear()
{
	xpos = CHARSIZE_X / 2;
	ypos = CHARSIZE_Y / 2;


	memset(m_mem, m_backColor, m_fb->iSize);

}
void Framebuffer::SetPixel(unsigned long x, unsigned long y, uint32_t cl)
{	
	if(m_fb->iDepth == 24)
		SetPixel24(x,y, cl);
	else if(m_fb->iDepth == 16)
		SetPixel16(x,y, cl);
}
void Framebuffer::SetPixel(unsigned long x, unsigned long y, int r, int g, int b)
{
	if(m_fb->iDepth == 24)
		SetPixel24(x,y, r,g,b);
	else if(m_fb->iDepth == 16)
		SetPixel16(x,y, r,g,b);
}
void Framebuffer::SetPixel16(unsigned long x, unsigned long y, uint32_t cl)
{
	if (x > m_fb->ifbX || y > m_fb->ifbY) return;
	// calculate the pixel's byte offset inside the buffer
    // note: x * 2 as every pixel is 2 consecutive bytes
    unsigned int pix_offset = x * 2 + y * m_fb->iPitch;
    // but a bit more complicated for RGB565
    // r = 
    unsigned short c = ((((cl>>16) & 0xff)  / 8) << 11) + (( ((cl>>8) & 0xff) / 4) << 5) + ((cl & 0xff)  / 8);

    *((unsigned short*)(m_mem + pix_offset)) = c;
}
void Framebuffer::SetPixel24(unsigned long x, unsigned long y, uint32_t cl)
{
	register unsigned char *ptmp;

	if (x > m_fb->ifbX || y > m_fb->ifbY) return;

	x = (x * (m_fb->iDepth >> 3));
	y = (y * m_fb->iPitch);

	unsigned char *asd = (unsigned char *)m_mem;
	ptmp = &asd[x+y];
	ptmp[2] = cl & 0xff;
	ptmp[1] = (cl>>8) & 0xff;
	ptmp[0] = (cl>>16) & 0xff;
}
void Framebuffer::SetPixel16(unsigned long x, unsigned long y, int r, int g, int b)
{
	if (x > m_fb->ifbX || y > m_fb->ifbY) return;
	// calculate the pixel's byte offset inside the buffer
    // note: x * 2 as every pixel is 2 consecutive bytes
    unsigned int pix_offset = x * 2 + y * m_fb->iPitch;
    // but a bit more complicated for RGB565
    unsigned short c = ((r / 8) << 11) + ((g / 4) << 5) + (b / 8);

    *((unsigned short*)(m_mem + pix_offset)) = c;
}
void Framebuffer::SetPixel24(unsigned long x, unsigned long y, int r, int g, int b)
{
	register unsigned char *ptmp;

	if (x > m_fb->ifbX || y > m_fb->ifbY) return;

	x = (x * (m_fb->iDepth >> 3));
	y = (y * m_fb->iPitch);

	unsigned char *asd = (unsigned char *)m_mem;
	ptmp = &asd[x+y];
	ptmp[0] = b;
	ptmp[1] = g;
	ptmp[2] = r;
}
void Framebuffer::WriteChar(char c)
{
	InternalWrite(c);
}
void Framebuffer::Write(const char* cp)
{
	const char *str = cp, *ch;
	for(ch = str; *ch; ch++) 
	{
		if(ch) InternalWrite(*ch);
	}
	delete[] str;
}
uint64_t Framebuffer::Write(uint8_t *cp, uint64_t offset, uint64_t size)
{
	unsigned char *str = cp;

	for(uint64_t i= 0; i < size; i++)
	{
		InternalWrite(str[i]);
	}
	delete[] str;
	return size;
}
void Framebuffer::TextColor(uint16_t color)
{
	switch(color)
	{//RGB
		case CGA_COLOR_BLACK: m_txtColor = 0x000000; break;
		case CGA_COLOR_WHITE: m_txtColor = 0xFFFFFF; break;
		case CGA_COLOR_BLUE: m_txtColor = 0x0000FF; break;
		case CGA_COLOR_GREEN: m_txtColor = 0x00AA00; break;
		case CGA_COLOR_RED: m_txtColor = 0xFF0000; break;
		case CGA_COLOR_MAGENTA: m_txtColor = 0xff0090; break;
		case CGA_COLOR_CYAN: m_txtColor = 0x00ddff; break;
		case CGA_COLOR_LCYAN: m_txtColor = 0x00ffff; break;
		case CGA_COLOR_YELLOW: m_txtColor = 0xFFFF00; break;
		case CGA_COLOR_LMAGENTA: m_txtColor = 0xff69b4; break;
		case CGA_COLOR_PINK: m_txtColor = 0xffb6c1; break;
		case CGA_COLOR_LGREY: m_txtColor = 0xA5A5A5; break;
		case CGA_COLOR_DGREY: m_txtColor = 0x555555; break;
		case CGA_COLOR_BROWN: m_txtColor = 0x963F20; break;
		case CGA_COLOR_LBLUE: m_txtColor = 0x8080FF; break;
		case CGA_COLOR_LGREEN: m_txtColor = 0x00FF00; break;
	};
}
void Framebuffer::BackColor(uint16_t color)
{
	switch(color)
	{//RGB
		case CGA_COLOR_BLACK: m_backColor = 0x000000; break;
		case CGA_COLOR_WHITE: m_backColor = 0xFFFFFF; break;
		case CGA_COLOR_BLUE: m_backColor = 0x0000FF; break;
		case CGA_COLOR_GREEN: m_backColor = 0x00AA00; break;
		case CGA_COLOR_RED: m_backColor = 0xFF0000; break;
		case CGA_COLOR_MAGENTA: m_backColor = 0xff0090; break;
		case CGA_COLOR_CYAN: m_backColor = 0x00ddff; break;
		case CGA_COLOR_LCYAN: m_backColor = 0x00ffff; break;
		case CGA_COLOR_YELLOW: m_backColor = 0xFFFF00; break;
		case CGA_COLOR_LMAGENTA: m_backColor = 0xff69b4; break;
		case CGA_COLOR_PINK: m_backColor = 0xffb6c1; break;
		case CGA_COLOR_LGREY: m_backColor = 0xA5A5A5; break;
		case CGA_COLOR_DGREY: m_backColor = 0x555555; break;
		case CGA_COLOR_BROWN: m_backColor = 0x963F20; break;
		case CGA_COLOR_LBLUE: m_backColor = 0x8080FF; break;
		case CGA_COLOR_LGREEN: m_backColor = 0x00FF00; break;
	};
}