#ifndef __FB_GHD_HPP__
#define __FB_GHD_HPP__

#include <dev/Framebuffer.hpp>

namespace fb
{
	class GraphicBuffer;
	class GraphicDevice
	{
	public:
		GraphicDevice();
		GraphicDevice(int deviceID);
		~GraphicDevice();
		void SwapBuffer(GraphicBuffer *buffer);

		GraphicBuffer*		CreateBuffer();
		::FrameBuffer	*GetFramebufferInfo()	{ return m_fb->GetKernelFrambuffer(); }
	private:
		dev::Framebuffer 	*m_fb;
	};

	typedef GraphicDevice GHD;
}
#endif
