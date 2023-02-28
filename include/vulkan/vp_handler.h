#pragma once

#include <glm/glm.hpp>
#include "push_constant.h"

namespace dragonbyte_engine
{
	class Camera;

	struct ViewProjectionData
	{
		glm::mat4 view;
		glm::mat4 proj;
	};

	namespace vulkan
	{

		class ViewProjectionHandler
		{
		public:

			ViewProjectionHandler();
			~ViewProjectionHandler();

			ViewProjectionData m_data;

			void push(Camera& camera);

		private:
	
			void set_view_proj_data(ViewProjectionData vpd);
			PushConstantRange<ViewProjectionData> m_pushConstantRange;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine