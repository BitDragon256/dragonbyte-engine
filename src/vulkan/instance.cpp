#include "vulkan/instance.h"

#include <stdexcept>

#include <GLFW/glfw3.h>

#include "vulkan/debug_messenger.h"
#include "vulkan/extensions.h"
#include "vulkan/validation_layers.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		Instance::Instance(const char* a_pAppName, const char* a_pEngineName)
		{
			if (validation_layers::kEnable && !validation_layers::check_support())
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
			auto extensions = get_required_extensions();

			// Instance Create Info
			VkInstanceCreateInfo instanceCreateInfo = {};
			instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			instanceCreateInfo.pApplicationInfo = &applicationInfo;

			instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
			instanceCreateInfo.ppEnabledExtensionNames = extensions.data();

			VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {};
			if (validation_layers::kEnable) {
				instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(validation_layers::kValidationLayers.size());
				instanceCreateInfo.ppEnabledLayerNames = validation_layers::kValidationLayers.data();

				DebugMessenger::populate_create_info(debugCreateInfo);
				instanceCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
			} else {
				instanceCreateInfo.enabledLayerCount = 0;
				instanceCreateInfo.pNext = nullptr;
			}

			// Create Vulkan Instance
			VkResult res = vkCreateInstance(&instanceCreateInfo, nullptr, &m_instance);
			if (res != VK_SUCCESS)
				throw std::runtime_error("Failed to create instance");
		}

		Instance::~Instance()
		{
			vkDestroyInstance(m_instance, nullptr);
		}

	} // namespace vulkan

} // namespace dragonbyte_engine