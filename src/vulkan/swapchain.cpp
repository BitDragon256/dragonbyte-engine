#include "vulkan/swapchain.h"

#include <cstdint>

#include <algorithm>
#include <limits>
#include <stdexcept>

namespace dragonbyte_engine
{

	namespace vulkan
	{

		SwapChain::SwapChain(
			const Window& a_krWindow,
			const PhysicalDevice& a_krPhysicalDevice,
			const LogicalDevice& a_krLogicalDevice
		) : m_krLogicalDevice{ a_krLogicalDevice }
		{
			// retrieve things the swapchain must support
			SwapChainSupportDetails swapChainSupport = query_swapchain_support(a_krPhysicalDevice.m_physicalDevice, a_krPhysicalDevice.m_krSurface);
		
			// choose the best surface-format, present-mode and extent
			VkSurfaceFormatKHR surfaceFormat = choose_swap_surface_format(swapChainSupport.formats);
			VkPresentModeKHR presentMode = choose_swap_present_mode(swapChainSupport.presentModes);
			VkExtent2D extent = choose_swap_extent(swapChainSupport.capabilities, a_krWindow);

			// choose a good image count
			uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
			if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
			{
				imageCount = swapChainSupport.capabilities.maxImageCount;
			}

			// fill out the create info struct
			VkSwapchainCreateInfoKHR createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			createInfo.surface = a_krPhysicalDevice.m_krSurface.m_surface;

			createInfo.minImageCount = imageCount;
			createInfo.imageFormat = surfaceFormat.format;
			createInfo.imageColorSpace = surfaceFormat.colorSpace;
			createInfo.imageExtent = extent;
			createInfo.imageArrayLayers = 1;
			createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

			// retrieve the queue family and set the sharing-mode accordingly
			QueueFamilyIndices indices = find_queue_families(a_krPhysicalDevice.m_physicalDevice, a_krPhysicalDevice.m_krSurface);
			uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

			if (indices.graphicsFamily != indices.presentFamily)
			{
				createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
				createInfo.queueFamilyIndexCount = 2;
				createInfo.pQueueFamilyIndices = queueFamilyIndices;
			}
			else
			{
				createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
				createInfo.queueFamilyIndexCount = 0; // Optional
				createInfo.pQueueFamilyIndices = nullptr; // Optional
			}

			// fill out the rest of the struct
			createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
			createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
			createInfo.presentMode = presentMode;
			createInfo.clipped = VK_TRUE;
			createInfo.oldSwapchain = VK_NULL_HANDLE;

			// create the swapchain handle
			VkResult res = vkCreateSwapchainKHR(a_krLogicalDevice.m_device, &createInfo, nullptr, &m_swapChain);
			if (res != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to create swapchain");
			}

			// save the image handles of the swapchain
			vkGetSwapchainImagesKHR(a_krLogicalDevice.m_device, m_swapChain, &imageCount, nullptr);
			m_swapChainImages.resize(imageCount);
			vkGetSwapchainImagesKHR(a_krLogicalDevice.m_device, m_swapChain, &imageCount, m_swapChainImages.data());
		
			// save some stuff
			m_swapChainImageFormat = surfaceFormat.format;
			m_swapChainExtent = extent;
		}
		SwapChain::~SwapChain()
		{
			vkDestroySwapchainKHR(m_krLogicalDevice.m_device, m_swapChain, nullptr);
		}

		VkSurfaceFormatKHR SwapChain::choose_swap_surface_format(const std::vector<VkSurfaceFormatKHR>& a_krAvailableFormats)
		{
			for (const auto& krAvailableFormat : a_krAvailableFormats)
			{
				if (krAvailableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && krAvailableFormat.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR)
				{
					return krAvailableFormat;
				}
			}

			// if no good one has been found
			return a_krAvailableFormats[0];
		}
		VkPresentModeKHR SwapChain::choose_swap_present_mode(const std::vector<VkPresentModeKHR>& a_krAvailablePresentModes)
		{
			for (const auto& krAvailablePresentMode : a_krAvailablePresentModes)
			{
				if (krAvailablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
				{
					return krAvailablePresentMode;
				}
			}

			// if nothing else is supported, return the only must-support
			return VK_PRESENT_MODE_FIFO_KHR;
		}
		VkExtent2D SwapChain::choose_swap_extent(const VkSurfaceCapabilitiesKHR& a_krCapabilities, const Window& a_krWindow)
		{
			if (a_krCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
			{
				return a_krCapabilities.currentExtent;
			}
			else
			{
				int width, height;
				glfwGetFramebufferSize(a_krWindow.m_pGlfwWindow, &width, &height);

				VkExtent2D actualExtent = {
					static_cast<uint32_t>(width),
					static_cast<uint32_t>(height)
				};

				actualExtent.width = std::clamp(actualExtent.width, a_krCapabilities.minImageExtent.width, a_krCapabilities.maxImageExtent.width);
				actualExtent.height = std::clamp(actualExtent.height, a_krCapabilities.minImageExtent.height, a_krCapabilities.maxImageExtent.height);
			
				return actualExtent;
			}
		}

		SwapChainSupportDetails query_swapchain_support(const VkPhysicalDevice& a_krPhysicalDevice, const Surface& a_krSurface) {
			SwapChainSupportDetails details;

			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(a_krPhysicalDevice, a_krSurface.m_surface, &details.capabilities);

			uint32_t formatCount;
			vkGetPhysicalDeviceSurfaceFormatsKHR(a_krPhysicalDevice, a_krSurface.m_surface, &formatCount, nullptr);

			if (formatCount != 0) {
				details.formats.resize(formatCount);
				vkGetPhysicalDeviceSurfaceFormatsKHR(a_krPhysicalDevice, a_krSurface.m_surface, &formatCount, details.formats.data());
			}

			uint32_t presentModeCount;
			vkGetPhysicalDeviceSurfacePresentModesKHR(a_krPhysicalDevice, a_krSurface.m_surface, &presentModeCount, nullptr);

			if (presentModeCount != 0) {
				details.presentModes.resize(presentModeCount);
				vkGetPhysicalDeviceSurfacePresentModesKHR(a_krPhysicalDevice, a_krSurface.m_surface, &presentModeCount, details.presentModes.data());
			}

			return details;
		}

	} // namespace vulkan

} // namespace dragonbyte_engine