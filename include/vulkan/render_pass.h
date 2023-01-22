#pragma once

#include <vulkan/vulkan.h>

#include "logical_device.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{
		struct ObjectInfo;

		class RenderPass
		{

		public:

			RenderPass();
			~RenderPass();
			
			VkRenderPass m_renderPass;

			void begin(uint32_t a_kImageIndex);

		private:

			const LogicalDevice& m_krLogicalDevice;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine