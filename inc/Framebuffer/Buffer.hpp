#ifndef __FB_BUFFER_HPP__
#define __FB_BUFFER_HPP__

#include <Framebuffer/GraphicDevice.hpp>

namespace fb
{
	class GraphicBuffer
	{
	public:
		GraphicBuffer();
		~GraphicBuffer();

		void Create(GraphicDevice *device);
		void Pixel(unsigned long x, unsigned long y, uint32_t cl);
		void Pixel(unsigned long x, unsigned long y, int r, int g, int b);

		void Swap(GraphicBuffer* buffer);
		void Clear() { memset(m_pBuffer, 0, m_iSize); }

		uint32_t Width()	{ return m_iScreenWidth; }
		uint32_t Height()	{ return m_iScreenHeight; }
		uint32_t Depth()	{ return m_iBitsPerPixel; }
		uint32_t Size()		{ return m_iSize; }

		unsigned char* rawBuffer() { return m_pBuffer; }
	protected:
		void Pixel16(unsigned long x, unsigned long y, uint32_t cl);
		void Pixel24(unsigned long x, unsigned long y, uint32_t cl);

		void Pixel16(unsigned long x, unsigned long y, int r, int g, int b);
		void Pixel24(unsigned long x, unsigned long y, int r, int g, int b);
	private:
		unsigned char*	m_pBuffer;
	
		uint32_t	m_iScreenWidth;
		uint32_t	m_iScreenHeight;
		uint32_t	m_iBitsPerPixel;
		uint32_t 	m_iSize;
		uint32_t 	m_iPitch;
	};
}
#endif
