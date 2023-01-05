#pragma once

#include <vector>

#include <vulkan/vulkan.h>

namespace dragonbyte_engine
{

	namespace vulkan
	{

		class Instance
		{
		public:

			Instance(const char* a_pAppName, const char* a_pEngineName);
			~Instance();

			Instance(const Instance&) = delete;
			Instance& operator=(const Instance&) = delete;

			VkInstance m_instance;

		private:

			std::vector<VkExtensionProperties> m_enabledExtensions;

		};

	} // namespace vulkan

} // namespace dragonbyte_engine