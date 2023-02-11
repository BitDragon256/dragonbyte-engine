#include "vulkan/vp_handler.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		ViewProjectionHandler::ViewProjectionHandler()
		{
			m_pushConstantRange.create(1);
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