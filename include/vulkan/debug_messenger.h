#pragma once

#include <vulkan/vulkan.h>

#include "instance.h"

namespace dragonbyte_engine
{

    namespace vulkan
    {

        class DebugMessenger
        {

        public:

            DebugMessenger(const Instance& a_krInstance);
            ~DebugMessenger();

            VkDebugUtilsMessengerEXT m_debugMessenger;

            static void populate_create_info(VkDebugUtilsMessengerCreateInfoEXT& a_rCreateInfo);

        private:
            
            const Instance& m_krInstance;

        };

    } // namespace vulkan


} // namespace dragonbyte_engine