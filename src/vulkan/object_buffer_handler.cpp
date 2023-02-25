#include "vulkan/object_buffer_handler.h"

#include "vulkan/object_info.h"
#include "vulkan/swapchain.h"
#include "tools.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{
		ObjectBufferHandler::ObjectBufferHandler()
		{
			destruct();
		}
		ObjectBufferHandler::~ObjectBufferHandler()
		{

		}

		void ObjectBufferHandler::create()
		{
			m_buffers.resize(oi.pSwapChain->m_images.size());
			m_data.reserve(OBJECT_BUFFER_HANDLER_DEFAULT_SIZE);
			for (size_t i = 0; i < m_buffers.size(); i++)
			{
				m_buffers[i].create(
					OBJECT_BUFFER_HANDLER_DEFAULT_SIZE,
					sizeof(ObjectData),
					true,
					VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
					VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
				);
			}
		}
		void ObjectBufferHandler::destruct()
		{
			m_buffers = {  };
			m_data = {  };
		}
		void ObjectBufferHandler::set_data(const std::vector<ObjectData>& a_krData)
		{
			if (a_krData.size() > m_data.capacity())
			{
				size_t newSize = static_cast<size_t>(floor((double)a_krData.size() / OBJECT_BUFFER_HANDLER_SIZE_STEP + 1));
				resize_buffers(newSize);
			}

			m_data = a_krData;
		}
		void ObjectBufferHandler::push_data(uint32_t a_frame)
		{
			m_buffers[a_frame].copy_data(m_data);
		}
		std::vector<VkBuffer> ObjectBufferHandler::get_buffers()
		{
			std::vector<VkBuffer> buffers;
			for (size_t i = 0; i < m_buffers.size(); i++)
			{
				buffers.push_back(m_buffers[i].m_buffer);
			}
			return buffers;
		}
		void ObjectBufferHandler::resize_buffers(size_t a_size)
		{
			for (size_t i = 0; i < m_buffers.size(); i++)
			{
				m_buffers[i].resize(a_size);
			}
		}

	} // namespace vulkan

} // namespace dragonbyte_engine