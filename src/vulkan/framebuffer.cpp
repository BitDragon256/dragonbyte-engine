#include "vulkan/framebuffer.h"

#include <array>

#include "vulkan/object_info.h"

#include "vulkan/render_pass.h"
#include "vulkan/swapchain.h"
#include "vulkan/depth_handler.h"

namespace dragonbyte_engine
{
	namespace vulkan
	{

		size_t Framebuffer::s_swapchainImageIndex = 0;
		Framebuffer::Framebuffer() :
			m_pLogicalDevice{ oi.pLogicalDevice }
		{
			std::array<VkImageView, 2> attachments = {
				oi.pSwapChain->m_imageViews[s_swapchainImageIndex],
				oi.pDepthHandler->m_image.m_imageView
			};

			VkFramebufferCreateInfo framebufferInfo = {};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = oi.pRenderPass->m_renderPass;
			framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
			framebufferInfo.pAttachments = attachments.data();
			framebufferInfo.width = oi.pSwapChain->m_extent.width;
			framebufferInfo.height = oi.pSwapChain->m_extent.height;
			framebufferInfo.layers = 1;

			VkResult res = vkCreateFramebuffer(oi.pLogicalDevice->m_device, &framebufferInfo, nullptr, &m_framebuffer);
			if (res != VK_SUCCESS)
				throw std::runtime_error("Failed to create framebuffer no " + s_swapchainImageIndex);

			s_swapchainImageIndex++;
		}
		Framebuffer::~Framebuffer()
		{
			vkDestroyFramebuffer(m_pLogicalDevice.lock()->m_device, m_framebuffer, nullptr);
		}

		FramebufferHandler::FramebufferHandler()
		{
			Framebuffer::s_swapchainImageIndex = 0;
			size_t imageCount = oi.pSwapChain->m_imageViews.size();
			m_swapChainFramebuffers.resize(imageCount);
			for (size_t i = 0; i < imageCount; i++)
			{
				m_swapChainFramebuffers[i] = new Framebuffer();
			}
		}
		FramebufferHandler::~FramebufferHandler()
		{
			for (size_t i = 0; i < m_swapChainFramebuffers.size(); i++)
			{
				delete m_swapChainFramebuffers[i];
			}
		}

		Framebuffer& FramebufferHandler::get(size_t index)
		{
			return *m_swapChainFramebuffers.at(index);
		}

	} // namespace vulkan

} // namespace dragonbyte_engine