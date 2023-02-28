#include "vulkan/vp_handler.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/gtc/matrix_transform.hpp>

#include "vulkan/object_info.h"
#include "vulkan/swapchain.h"
#include "default_components/camera.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		void ViewProjectionHandler::set_view_proj_data(ViewProjectionData a_vpd)
		{
			m_pushConstantRange.set(a_vpd, 0);
		}
		ViewProjectionHandler::ViewProjectionHandler()
		{
			m_pushConstantRange.create(1);
			ViewProjectionData vpd;

			vpd.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			vpd.proj = glm::perspective(glm::radians(45.0f), vulkan::oi.pSwapChain->m_extent.width / (float)vulkan::oi.pSwapChain->m_extent.height, 0.1f, 10.0f);
			vpd.proj[1][1] *= -1;

			set_view_proj_data(vpd);
		}
		ViewProjectionHandler::~ViewProjectionHandler()
		{

		}

		void ViewProjectionHandler::push(Camera& a_rCamera)
		{
			set_view_proj_data({
				a_rCamera.get_view_matrix(),
				a_rCamera.get_proj_matrix()
			});
			m_pushConstantRange.push();
		}

	} // namespace vulkan

} // namespace dragonbyte_engine