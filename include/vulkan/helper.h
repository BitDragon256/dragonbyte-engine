#pragma once

#include <stdexcept>

#include <vulkan/vulkan.h>

namespace dragonbyte_engine
{

	namespace vulkan
	{

		class Helper
		{
		public:
			static void check_result(VkResult a_res, const char* a_pError)
			{
				if (a_res != VK_SUCCESS)
					throw std::runtime_error(a_pError);
			}
		};

	} // namespace vulkan

} // namespace dragonbyte_engine