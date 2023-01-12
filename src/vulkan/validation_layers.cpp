#include "vulkan/validation_layers.h"

#include <cstring>

#include <vulkan/vulkan.h>

namespace dragonbyte_engine
{
    
    namespace vulkan
    {

        bool check_validation_layer_support()
        {
            uint32_t layerCount;
            vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

            std::vector<VkLayerProperties> availableLayers(layerCount);
            vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

            for (const char* layerName : kValidationLayers)
            {
                bool layerFound = false;

                for (const auto& layerProperties : availableLayers) {
                    if (strcmp(layerName, layerProperties.layerName) == 0) {
                        layerFound = true;
                        break;
                    }
                }

                if (!layerFound) {
                    return false;
                }
            }

            return true;
        }

    } // namespace vulkan
    

} // namespace dragonbyte_engine
