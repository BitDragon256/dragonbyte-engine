#include "vulkan/object_buffer_handler.h"

#include "vulkan/object_info.h"
#include "vulkan/swapchain.h"
#include "tools.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
			m_data.resize(OBJECT_BUFFER_HANDLER_DEFAULT_SIZE);

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

			for (size_t i = 0; i < a_krData.size(); i++)
			{
				m_data[i] = a_krData[i];
			}
			//m_data = a_krData;
		}
		void ObjectBufferHandler::push_data(uint32_t a_frame)
		{
			/*
			for (auto& data : m_data)
			{
				data.model = glm::identity<glm::mat4>();
				//data.model = glm::mat4{ { 1, 1, 1, 1 },{ 1, 1, 1, 1 },{ 1, 1, 1, 1 },{ 1, 1, 1, 1 } };
			}
			*/
			//m_buffers[a_frame].copy_data(m_data);

			ObjectData* objectData = (ObjectData*)m_buffers[a_frame].mapped_memory();
			for (size_t i = 0; i < m_data.size(); i++)
			{
				objectData[i].model = m_data[i].model;
			}
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