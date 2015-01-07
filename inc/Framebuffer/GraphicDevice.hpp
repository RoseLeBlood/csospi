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
		KernelFrameBuffer	*GetFramebufferInfo()	{ return m_fbb; }
	private:
		dev::Framebuffer 	*m_fb;
		KernelFrameBuffer 	*m_fbb;
	};

	typedef GraphicDevice GHD;
}
#endif
