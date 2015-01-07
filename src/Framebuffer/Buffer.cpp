#include <types.h>
#include <Framebuffer/Buffer.hpp>
#include <malloc.h>
#include <stdio.h>

extern unsigned char font8x8_basic[128][8];

namespace fb
{
	GraphicBuffer::GraphicBuffer()
	{
		
	}
    GraphicBuffer::~GraphicBuffer()
    {
    	if(m_pBuffer != 0) { free(m_pBuffer); m_pBuffer = NULL; }
    }
    void GraphicBuffer::Create(GraphicDevice *device)
    {
    	KernelFrameBuffer *info = device->GetFramebufferInfo();

		m_iScreenWidth = info->ifbX;
		m_iScreenHeight = info->ifbY;
		m_iBitsPerPixel = info->iDepth;
		m_iPitch =info->iPitch;
		m_iSize = info->iSize;

		m_pBuffer = ((unsigned char *) (malloc(info->iSize)));

		if(m_pBuffer != 0)
			printf("Create buffer: %dx%d-%d %d\n", m_iScreenWidth, m_iScreenHeight, m_iBitsPerPixel,   info->iSize );
    }
	void GraphicBuffer::Pixel(unsigned long x, unsigned long y, uint32_t cl)
	{
		if(m_iBitsPerPixel == 16)
			Pixel16(x,y,cl);
		else if(m_iBitsPerPixel == 24)
			Pixel24(x,y,cl);
	}
	void GraphicBuffer::Pixel(unsigned long x, unsigned long y, int r, int g, int b)
	{
		if(m_iBitsPerPixel == 16)
			Pixel16(x,y,r,g,b);
		else if(m_iBitsPerPixel == 24)
			Pixel24(x,y,r,g,b);
	}
	void GraphicBuffer::Swap(GraphicBuffer* buffer)
	{
		memcpy(m_pBuffer, buffer->m_pBuffer, m_iSize);
	}
	void GraphicBuffer::Pixel16(unsigned long x, unsigned long y, uint32_t cl)
	{
		if (x > m_iScreenWidth || y > m_iScreenHeight) return;
    	unsigned int pix_offset = x * 2 + y * m_iPitch;
    	unsigned short c = (( (cl & 0xff) / 8) << 11) + (( ((cl>>8) & 0xff) / 4) << 5) + ( ((cl>>16) & 0xff) / 8);

    	*((unsigned short*)(m_pBuffer + pix_offset)) = c;
	}
	void GraphicBuffer::Pixel24(unsigned long x, unsigned long y, uint32_t cl)
	{
		register unsigned char *ptmp;

		if (x > m_iScreenWidth || y > m_iScreenHeight) return;

		x = (x * (m_iBitsPerPixel >> 3));
		y = (y * m_iPitch);

		unsigned char *asd = (unsigned char *)m_pBuffer;
		ptmp = &asd[x+y];
		ptmp[0] = cl & 0xff;
		ptmp[1] = (cl>>8) & 0xff;
		ptmp[2] = (cl>>16) & 0xff;
	}
	void GraphicBuffer::Pixel16(unsigned long x, unsigned long y, int r, int g, int b)
	{
		if (x > m_iScreenWidth || y > m_iScreenHeight) return;
    	unsigned int pix_offset = x * 2 + y * m_iPitch;
    	unsigned short c = ((r / 8) << 11) + ((g / 4) << 5) + (b / 8);

    	*((unsigned short*)(m_pBuffer + pix_offset)) = c;
	}
	void GraphicBuffer::Pixel24(unsigned long x, unsigned long y, int r, int g, int b)
	{
		register unsigned char *ptmp;

		if (x > m_iScreenWidth || y > m_iScreenHeight) return;

		x = (x * (m_iBitsPerPixel >> 3));
		y = (y * m_iPitch);

		unsigned char *asd = (unsigned char *)m_pBuffer;
		ptmp = &asd[x+y];
		ptmp[0] = r & 0xff;
		ptmp[1] = g & 0xff;
		ptmp[2] = b & 0xff;
	}
}