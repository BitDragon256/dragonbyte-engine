#include "vulkan/mvp_buffer_handler.h"

#include "vulkan/object_info.h"
#include "vulkan/swapchain.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		MVPBufferHandler::MVPBufferHandler()
		{
			m_buffers.resize(oi.pSwapChain->m_images.size());
			for (size_t i = 0; i < m_buffers.size(); i++)
			{
				m_buffers[i].create(
					10,
					sizeof(MVP),
					true,
					VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
					VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
				);
			}
		}
		MVPBufferHandler::~MVPBufferHandler()
		{

		}

		void MVPBufferHandler::push_data(uint32_t a_frame)
		{
			m_mvps[0].model[3][1] = 1;
			/*for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
					std::cout << m_mvps[2].model[i][j] << " ";
				std::cout << '\n';
			}*/
			
			m_buffers[a_frame].copy_data(m_mvps);
		}
		std::vector<VkBuffer> MVPBufferHandler::get_buffers()
		{
			std::vector<VkBuffer> buffers;
			for (size_t i = 0; i < m_buffers.size(); i++)
			{
				buffers.push_back(m_buffers[i].m_buffer);
			}
			return buffers;
		}

	} // namespace vulkan

} // namespace dragonbyte_engine