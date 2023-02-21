#include "vulkan/vp_handler.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/gtc/matrix_transform.hpp>

#include "vulkan/object_info.h"
#include "vulkan/swapchain.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		ViewProjectionHandler::ViewProjectionHandler()
		{
			m_pushConstantRange.create(1);
			ViewProjectionData vpd;

			vpd.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			vpd.proj = glm::perspective(glm::radians(45.0f), vulkan::oi.pSwapChain->m_extent.width / (float)vulkan::oi.pSwapChain->m_extent.height, 0.1f, 10.0f);
			vpd.proj[1][1] *= -1;

			m_pushConstantRange.set(vpd, 0);
		}
		ViewProjectionHandler::~ViewProjectionHandler()
		{

		}

		void ViewProjectionHandler::push()
		{
			m_pushConstantRange.push();
		}

	} // namespace vulkan

} // namespace dragonbyte_engine