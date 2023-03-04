#include "vulkan/descriptor_pool.h"

#include <stdexcept>

#include "vulkan/object_info.h"

#include "vulkan/logical_device.h"
#include "vulkan/swapchain.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		DescriptorPool::DescriptorPool() {}
		DescriptorPool::~DescriptorPool()
		{
			vkDestroyDescriptorPool(oi.pLogicalDevice->m_device, m_descriptorPool, nullptr);
		}

		void DescriptorPool::create(std::vector<VkDescriptorType> a_descriptorTypes, std::vector<uint32_t> a_descriptorCounts)
		{
			std::vector<VkDescriptorPoolSize> poolSizes{ a_descriptorTypes.size() };
			for (size_t i = 0; i < a_descriptorTypes.size(); i++)
			{
				poolSizes[i].type = a_descriptorTypes[i];
				poolSizes[i].descriptorCount = a_descriptorCounts[i];
			}

			VkDescriptorPoolCreateInfo poolInfo = {};
			poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
			poolInfo.pPoolSizes = poolSizes.data();

			poolInfo.maxSets = static_cast<uint32_t>(oi.pSwapChain->m_images.size());

			VkResult res = vkCreateDescriptorPool(oi.pLogicalDevice->m_device, &poolInfo, nullptr, &m_descriptorPool);
			if (res != VK_SUCCESS)
				throw std::runtime_error("Failed to create Descriptor Pool");
		}

	} // namespace vulkan

} // namespace dragonbyte_engine