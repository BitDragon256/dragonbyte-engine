#pragma once

#include <vulkan/vulkan.h>

#include "object_info.h"

namespace dragonbyte_engine
{

    namespace vulkan
    {

        class CommandPool
        {
        public:

            CommandPool(const ObjectInfo& a_krObjectInfo);
            ~CommandPool();

            VkCommandPool m_commandPool;

        };

    }; // namespace vulkan

}; // namespace dragonbyte_engine