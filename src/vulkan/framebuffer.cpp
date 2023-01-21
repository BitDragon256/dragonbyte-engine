#include "vulkan/framebuffer.h"

#include "vulkan/object_info.h"

#include "vulkan/render_pass.h"
#include "vulkan/swapchain.h"

namespace dragonbyte_engine
{
	namespace vulkan
	{

		size_t Framebuffer::s_swapchainImageIndex = 0;
		Framebuffer::Framebuffer(const ObjectInfo& a_krObjectInfo) :
			m_pLogicalDevice{ a_krObjectInfo.pLogicalDevice }
		{
			VkImageView attachments[] = {
				a_krObjectInfo.pSwapChain->m_imageViews[s_swapchainImageIndex]
			};

			VkFramebufferCreateInfo framebufferInfo = {};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = a_krObjectInfo.pRenderPass->m_renderPass;
			framebufferInfo.attachmentCount = 1;
			framebufferInfo.pAttachments = attachments;
			framebufferInfo.width = a_krObjectInfo.pSwapChain->m_extent.width;
			framebufferInfo.height = a_krObjectInfo.pSwapChain->m_extent.height;
			framebufferInfo.layers = 1;

			VkResult res = vkCreateFramebuffer(a_krObjectInfo.pLogicalDevice->m_device, &framebufferInfo, nullptr, &m_framebuffer);
			if (res != VK_SUCCESS)
				throw std::runtime_error("Failed to create framebuffer no " + s_swapchainImageIndex);

			s_swapchainImageIndex++;
		}
		Framebuffer::Framebuffer()
		{
		
		}
		Framebuffer::~Framebuffer()
		{
			vkDestroyFramebuffer(m_pLogicalDevice.lock()->m_device, m_framebuffer, nullptr);
		}

		FramebufferHandler::FramebufferHandler(const ObjectInfo& a_krObjectInfo)
		{
			Framebuffer::s_swapchainImageIndex = 0;
			size_t imageCount = a_krObjectInfo.pSwapChain->m_imageViews.size();
			m_swapChainFramebuffers.resize(imageCount);
			for (size_t i = 0; i < imageCount; i++)
			{
				m_swapChainFramebuffers[i] = new Framebuffer{ a_krObjectInfo };
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