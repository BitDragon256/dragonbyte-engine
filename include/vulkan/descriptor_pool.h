#pragma once

#include <vector>

#include <vulkan/vulkan.h>

namespace dragonbyte_engine
{

	namespace vulkan
	{

		class DescriptorPool
		{
		public:
			DescriptorPool();
			~DescriptorPool();

			void create(std::vector<VkDescriptorType> descriptorTypes, std::vector<uint32_t> descriptorCounts);

			VkDescriptorPool m_descriptorPool;
		};

	} // namespace vulkan

} // namespace dragonbyte_engine