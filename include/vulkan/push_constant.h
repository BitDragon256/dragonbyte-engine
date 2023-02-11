#pragma once

#include <vector>

#include <vulkan/vulkan.h>

#include "object_info.h"
#include "command_buffer.h"
#include "graphics_pipeline.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		template<class T>
		class PushConstantRange
		{
		public:

			PushConstantRange() :
				m_created{ false }
			{
				
			}
			~PushConstantRange() {}

			void create(size_t a_size)
			{
				if (!m_created)
				{
					m_rangeBegin = s_totalRangeSize;
					s_totalRangeSize += a_size * sizeof(T);

					m_rangeSize = a_size * sizeof(T);

					m_data.resize(a_size);
				}
			}
			void set(T a_data, size_t index)
			{
				if (m_created)
				{
					m_data[index] = a_data;
				}
			}
			void push()
			{
				if (m_created)
				{
					vkCmdPushConstants(
						oi.pCommandBuffer->m_commandBuffer,
						oi.pGraphicsPipeline->m_pipelineLayout,
						m_stages,
						m_rangeBegin,
						m_rangeSize,
						m_data.data()
					);
				}
			}

			std::vector<T> m_data;

		private:

			bool m_created;

			static size_t s_totalRangeSize;
			size_t m_rangeBegin;
			size_t m_rangeSize;

			VkPushConstantRange m_range;
			VkShaderStageFlags m_stages;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine