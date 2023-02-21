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
		struct AllPushConstantRanges
		{
		public:
			static std::vector<VkPushConstantRange> s_ranges;
			static size_t s_size;
		};

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
					m_rangeBegin = AllPushConstantRanges::s_size;
					m_rangeSize = a_size * sizeof(T);
					m_data.resize(a_size);

					m_range.offset = static_cast<uint32_t>(m_rangeBegin);
					m_range.size = static_cast<uint32_t>(m_rangeSize);

					apply_default_stage_flags();
					m_range.stageFlags = m_stages;

					AllPushConstantRanges::s_size += m_rangeSize;
					AllPushConstantRanges::s_ranges.push_back(m_range);
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
						static_cast<uint32_t>(m_rangeBegin),
						static_cast<uint32_t>(m_rangeSize),
						m_data.data()
					);
				}
			}

			std::vector<T> m_data;

		private:

			bool m_created;

			size_t m_rangeBegin;
			size_t m_rangeSize;

			VkPushConstantRange m_range;
			VkShaderStageFlags m_stages;

			void apply_default_stage_flags()
			{
				m_stages = VK_SHADER_STAGE_VERTEX_BIT;
			}

		};

	} // namespace vulkan

} // namespace dragonbyte_engine