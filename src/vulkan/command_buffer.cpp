#include "vulkan/command_buffer.h"

#include <stdexcept>

#include "vulkan/command_pool.h"
#include "vulkan/logical_device.h"

namespace dragonbyte_engine
{

    namespace vulkan
    {
    
        CommandBuffer::CommandBuffer()
        {
            VkCommandBufferAllocateInfo bufferInfo = {};
            bufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
            bufferInfo.commandPool = oi.pCommandPoolHandler->get_command_pool(CP_GRAPHICS)->m_commandPool;
            bufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
            bufferInfo.commandBufferCount = 1;
            
            VkResult res = vkAllocateCommandBuffers(oi.pLogicalDevice->m_device, &bufferInfo, &m_commandBuffer);
            if (res != VK_SUCCESS)
                throw std::runtime_error("Failed to allocate Command buffer");
        }
        CommandBuffer::~CommandBuffer()
        {
        
        }
        
        void CommandBuffer::begin_recording(const uint32_t a_kImageIndex)
        {
            vkResetCommandBuffer(m_commandBuffer, 0);
        
            VkCommandBufferBeginInfo beginInfo = {};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            beginInfo.flags = 0;
            beginInfo.pInheritanceInfo = nullptr;
            
            VkResult res = vkBeginCommandBuffer(m_commandBuffer, &beginInfo);
            if (res != VK_SUCCESS)
                throw std::runtime_error("Failed to begin Command Buffer Recording");
        }
    
    }; // namespace vulkan

}; //nnamespace dragonbyte_engine