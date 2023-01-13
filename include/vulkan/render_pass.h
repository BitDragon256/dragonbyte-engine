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

			RenderPass(const ObjectInfo& a_krObjectInfo);
			~RenderPass();

			VkRenderPass m_renderPass;

		private:

			const LogicalDevice& m_krLogicalDevice;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine