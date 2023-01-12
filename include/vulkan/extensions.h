#pragma once

#include <vector>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include "validation_layers.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

        std::vector<const char*> get_required_extensions()
        {
            uint32_t glfwExtensionCount = 0;
            const char** ppGlfwExtensions;
            ppGlfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

            std::vector<const char*> extensions(ppGlfwExtensions, ppGlfwExtensions + glfwExtensionCount);

            if (validation_layers::kEnable) {
                extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            }

            return extensions;
        }

	} // namespace vulkan


} // namespace dragonbyte_engine