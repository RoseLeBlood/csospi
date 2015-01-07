#include <types.h>
#include <Framebuffer/GraphicDevice.hpp>
#include <Framebuffer/Buffer.hpp>
#include <stdio.h>

extern "C" void* GetDeviceByName(char* name);

namespace fb
{
	GraphicDevice::GraphicDevice()
	{	
		m_fb = (dev::Framebuffer *)GetDeviceByName("fb0");
		m_fbb = m_fb->GetKernelFrambuffer();

		printf("open Device /dev/fb0\n");
	}
	GraphicDevice::GraphicDevice(int deviceID)
	{

	}
	GraphicDevice::~GraphicDevice()
	{
		m_fb = NULL;
	}
	void GraphicDevice::SwapBuffer(GraphicBuffer *buffer)
	{
		
		m_fb->Swap(buffer->rawBuffer(), buffer->Size());
	}
	GraphicBuffer*		GraphicDevice::CreateBuffer()
	{
		GraphicBuffer* buffer= new GraphicBuffer();
		buffer->Create(this);

		return buffer;
	}
}
