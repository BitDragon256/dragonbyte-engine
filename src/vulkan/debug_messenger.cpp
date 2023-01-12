#include "vulkan/debug_messenger.h"

#include <stdexcept>

#include "vulkan/validation_layers.h"

namespace dragonbyte_engine
{

    namespace vulkan
    {

        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
            auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
            if (func != nullptr) {
                return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
            }
            else {
                return VK_ERROR_EXTENSION_NOT_PRESENT;
            }
        }
        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
            auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
            if (func != nullptr) {
                func(instance, debugMessenger, pAllocator);
            }
        }

        DebugMessenger::DebugMessenger(const Instance& a_krInstance) :
            m_krInstance{ a_krInstance }
        {
            if (!validation_layers::kEnable)
                return;

            VkDebugUtilsMessengerCreateInfoEXT createInfo;
            populate_create_info(createInfo);
            

            VkResult res = CreateDebugUtilsMessengerEXT(a_krInstance.m_instance, &createInfo, nullptr, &m_debugMessenger);
            if (res != VK_SUCCESS)
            {
                throw std::runtime_error("Failed to create debug messenger");
            }
        }
        DebugMessenger::~DebugMessenger()
        {
            DestroyDebugUtilsMessengerEXT(m_krInstance.m_instance, m_debugMessenger, nullptr);
        }

        void DebugMessenger::populate_create_info(VkDebugUtilsMessengerCreateInfoEXT& a_rCreateInfo)
        {
            a_rCreateInfo = {};

            a_rCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            a_rCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            a_rCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            a_rCreateInfo.pfnUserCallback = validation_layers::debug_callback;
            a_rCreateInfo.pUserData = nullptr; // Optional
        }

    } // namespace vulkan


} // namespace dragonbyte_engine