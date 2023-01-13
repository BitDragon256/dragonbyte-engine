#pragma once

#include <vulkan/vulkan.h>

// #include "object_info.h"

#include "instance.h"

namespace dragonbyte_engine
{

    namespace vulkan
    {
        struct ObjectInfo;

        class DebugMessenger
        {

        public:

            DebugMessenger(const ObjectInfo& a_krObjectInfo);
            ~DebugMessenger();

            VkDebugUtilsMessengerEXT m_debugMessenger;

            static void populate_create_info(VkDebugUtilsMessengerCreateInfoEXT& a_rCreateInfo);

        private:
            
            const Instance& m_krInstance;

        };

    } // namespace vulkan


} // namespace dragonbyte_engine