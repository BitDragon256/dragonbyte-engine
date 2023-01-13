#pragma once

#include <vulkan/vulkan.h>

namespace dragonbyte_engine
{

	namespace vulkan
	{
		struct ObjectInfo;

		class Framebuffer
		{
		public:

			Framebuffer(const ObjectInfo& a_krObjectInfo);
			~Framebuffer();
		};

		class FramebufferHandler
		{
		public:

			FramebufferHandler(const ObjectInfo& a_krObjectInfo);
			~FramebufferHandler();
		};

	} // namespace vulkan

} // namespace dragonbyte_engine