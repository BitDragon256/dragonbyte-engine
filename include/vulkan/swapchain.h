#include <vulkan/vulkan.h>

#include <vector>

#include "logical_device.h"
#include "physical_device.h"
#include "surface.h"
#include "window.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		class SwapChain
		{

		public:

			SwapChain(
				const Window& a_krWindow,
				const PhysicalDevice& a_krPhysicalDevice,
				const LogicalDevice& a_krLogicalDevice
			);
			~SwapChain();

			std::vector<VkImage> m_images;
			std::vector<VkImageView> m_imageViews;

		private:

			static VkSurfaceFormatKHR choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR>& a_krAvailableFormats);
			static VkPresentModeKHR choose_swap_present_mode(const std::vector<VkPresentModeKHR>& a_krAvailablePresentModes);
			static VkExtent2D choose_swap_extent(const VkSurfaceCapabilitiesKHR& a_krCapabilities, const Window& a_krWindow);

			void create_image_views();
			void destroy_image_views();

			const LogicalDevice& m_krLogicalDevice;

			VkSwapchainKHR m_swapChain;
			VkFormat m_imageFormat;
			VkExtent2D m_extent;

		};

		struct SwapChainSupportDetails {
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;
		};

		SwapChainSupportDetails query_swapchain_support(const VkPhysicalDevice& a_krDevice, const Surface& a_krSurface);

	} // namespace vulkan

} // namespace dragonbyte_engine