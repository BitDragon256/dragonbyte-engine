#pragma once

#include <vector>

namespace dragonbyte_engine
{

    namespace vulkan
    {
    
		const std::vector<const char*> kValidationLayers = {
		    "VK_LAYER_KHRONOS_validation"
		};

		#ifdef NDEBUG
			const bool kEnableValidationLayers = false;
		#else
			const bool kEnableValidationLayers = true;
		#endif

        bool check_validation_layer_support();

    } // namespace vulkan
    

} // namespace dragonbyte_engine