#include "vulkan/descriptor_pool.h"

#include <stdexcept>

#include "vulkan/object_info.h"

#include "vulkan/logical_device.h"
#include "vulkan/swapchain.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		DescriptorPool::DescriptorPool(VkDescriptorType a_descriptorType)
		{
			VkDescriptorPoolSize poolSize = {};
			poolSize.type = a_descriptorType;
			poolSize.descriptorCount = static_cast<uint32_t>(oi.pSwapChain->m_images.size());

			VkDescriptorPoolCreateInfo poolInfo = {};
			poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			poolInfo.poolSizeCount = 1;
			poolInfo.pPoolSizes = &poolSize;

			poolInfo.maxSets = static_cast<uint32_t>(oi.pSwapChain->m_images.size());

			VkResult res = vkCreateDescriptorPool(oi.pLogicalDevice->m_device, &poolInfo, nullptr, &m_descriptorPool);
			if (res != VK_SUCCESS)
				throw std::runtime_error("Failed to create Descriptor Pool");
		}
		DescriptorPool::~DescriptorPool()
		{
			vkDestroyDescriptorPool(oi.pLogicalDevice->m_device, m_descriptorPool, nullptr);
		}

	} // namespace vulkan

} // namespace dragonbyte_engine