#include "vulkan/uniform_buffer_handler.h"

#include "vulkan/object_info.h"
#include "vulkan/swapchain.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		UniformBufferHandler::UniformBufferHandler()
		{
			m_buffers.resize(oi.pSwapChain->m_images.size());
			for (size_t i = 0; i < m_buffers.size(); i++)
			{
				m_buffers[i].create(
					1,
					sizeof(UniformBufferObject),
					true,
					VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
					VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
				);
			}
		}
		UniformBufferHandler::~UniformBufferHandler()
		{

		}

		void UniformBufferHandler::push_data(uint32_t a_frame, UniformBufferObject a_ubo)
		{
			std::vector<UniformBufferObject> v = { a_ubo };
			m_buffers[a_frame].copy_data(v);
		}

	} // namespace vulkan

} // namespace dragonbyte_engine