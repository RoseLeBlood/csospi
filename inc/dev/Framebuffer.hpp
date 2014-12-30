#ifndef __CSOS_DEV_FRAMEBUFFER_HPP__
#define __CSOS_DEV_FRAMEBUFFER_HPP__

#include <dev/Driver.hpp>
#include <kernel/utils.h>

namespace dev
{
	class Framebuffer : public Driver
	{
	public:
		Framebuffer() : Driver("Framebuffer", "fb") { }


		virtual bool Probe();
		virtual void SetPixel(unsigned long x, unsigned long y, uint32_t cl);
		virtual void SetPixel(unsigned long x, unsigned long y, int r, int g, int b);
		virtual char ReadChar() { return ' '; }
		virtual void WriteChar(char c);
		virtual void Write(const char* c);
		virtual void GotoXY(unsigned short x, unsigned short y) 
		{
			xpos = x;
			ypos = y;
		}
		virtual void TextColor(uint16_t color);
		virtual void BackColor(uint16_t color);
		
		virtual uint64_t Read(uint8_t *data, uint64_t offset, uint64_t size) { return 0; }
		virtual uint64_t Write(uint8_t *data, uint64_t offset, uint64_t size);

		virtual void Clear();
	protected:
		void SetPixel16(unsigned long x, unsigned long y, uint32_t cl);
		void SetPixel24(unsigned long x, unsigned long y, uint32_t cl);

		void SetPixel16(unsigned long x, unsigned long y, int r, int g, int b);
		void SetPixel24(unsigned long x, unsigned long y, int r, int g, int b);
		virtual void put(char c);
	private:
		virtual void InternalWrite(char c);
	protected:
		unsigned m_fbseg;
		char* m_mem;

		::FrameBuffer *m_fb;

		unsigned int xpos=0, ypos=0;

		uint32_t	  m_txtColor;
		uint32_t      m_backColor;
	};
}
#endif