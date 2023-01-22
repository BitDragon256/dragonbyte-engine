#pragma once

#include <vulkan/vulkan.h>

#include <vector>

#include "framebuffer.h"
#include "logical_device.h"
#include "physical_device.h"
#include "surface.h"
#include "window.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{
		struct ObjectInfo;

		class SwapChain
		{

		public:

			SwapChain();
			~SwapChain();

			std::vector<VkImage> m_images;
			std::vector<VkImageView> m_imageViews;

			VkExtent2D m_extent;
			VkFormat m_imageFormat;
			VkSwapchainKHR m_swapChain;
			
			uint32_t acquire_next_image();

		private:

			static VkSurfaceFormatKHR choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR>& a_krAvailableFormats);
			static VkPresentModeKHR choose_swap_present_mode(const std::vector<VkPresentModeKHR>& a_krAvailablePresentModes);
			static VkExtent2D choose_swap_extent(const VkSurfaceCapabilitiesKHR& a_krCapabilities, const Window& a_krWindow);

			void create_image_views();
			void destroy_image_views();

			const LogicalDevice& m_krLogicalDevice;

		};

		struct SwapChainSupportDetails {
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;
		};

		SwapChainSupportDetails query_swapchain_support(const VkPhysicalDevice& a_krDevice, const Surface& a_krSurface);

	} // namespace vulkan

} // namespace dragonbyte_engine