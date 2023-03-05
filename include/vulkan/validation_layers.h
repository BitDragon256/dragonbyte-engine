#pragma once

#include <iostream>
#include <string.h>
#include <vector>

#include <vulkan/vulkan.h>

namespace dragonbyte_engine
{

    namespace vulkan
    {
    
        namespace validation_layers
        {

            const std::vector<const char*> kValidationLayers = {
                "VK_LAYER_KHRONOS_validation"
            };

#ifdef NDEBUG
            const bool kEnable = false;
#else
            const bool kEnable = true;
#endif
            const std::string kColorRed = "\033[31m";
            const std::string kColorYellow = "\033[33m";
            const std::string kColorLightBlue = "\033[34m";
            const std::string kColorWhite = "\033[37m";

            inline bool check_support()
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
                        std::cout << layerName << " not found" << '\n';
                        return false;
                    }
                }

                return true;
            }
            
            inline VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
                VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData
            )
            {
                //if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
                //    std::cerr << kColorWhite;
                if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
                    std::cerr << kColorLightBlue;
                else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
                    std::cerr << kColorYellow;
                else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
                    std::cerr << kColorRed;
                else
                    return VK_FALSE;

                std::string message{ pCallbackData->pMessage };
                std::vector<std::string> splitMessage;
                size_t posStart = 0, pos;
                while ((pos = message.find('|', posStart)) != std::string::npos)
                {
                    splitMessage.push_back(message.substr(posStart, pos - posStart));
                    posStart = pos + 1;
                }
                splitMessage.push_back(message.substr(posStart));

                std::cerr << "validation layer:\n";
                for (auto s : splitMessage)
                    std::cerr << "   " << s << '\n';
                std::cerr << "\033[0m" << std::endl;

                return VK_FALSE;
            }

        } // namespace validation_layers

    } // namespace vulkan
    

} // namespace dragonbyte_engine