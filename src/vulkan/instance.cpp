#include "vulkan/instance.h"

#include <stdexcept>

#include <GLFW/glfw3.h>

#include "vulkan/validation_layers.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		Instance::Instance(const char* a_pAppName, const char* a_pEngineName)
		{
			if (kEnableValidationLayers && !check_validation_layer_support())
			{
				throw std::runtime_error("validation layers requested, but not available!");
			}

			// Application Info
			VkApplicationInfo applicationInfo = {};
			applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			applicationInfo.pApplicationName = a_pAppName;
			applicationInfo.pEngineName = a_pEngineName;
			applicationInfo.apiVersion = VK_VERSION_1_3;
			applicationInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
			applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);

			// Required Extensions
			uint32_t glfwExtensionCount;
			const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

			// Instance Create Info
			VkInstanceCreateInfo instanceCreateInfo = {};
			instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			instanceCreateInfo.pApplicationInfo = &applicationInfo;
			instanceCreateInfo.enabledExtensionCount = glfwExtensionCount;
			instanceCreateInfo.ppEnabledExtensionNames = glfwExtensions;

			if (kEnableValidationLayers) {
				instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(kValidationLayers.size());
				instanceCreateInfo.ppEnabledLayerNames = kValidationLayers.data();
			} else {
				instanceCreateInfo.enabledLayerCount = 0;
			}

			// Create Vulkan Instance
			vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance);
		}

		Instance::~Instance()
		{
			vkDestroyInstance(m_instance, nullptr);
		}

	} // namespace vulkan

} // namespace dragonbyte_engine