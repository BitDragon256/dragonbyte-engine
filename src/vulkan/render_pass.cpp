#include "vulkan/render_pass.h"

#include <array>
#include <stdexcept>

#include "vulkan/object_info.h"
#include "vulkan/swapchain.h"
#include "vulkan/command_buffer.h"
#include "vulkan/depth_handler.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		RenderPass::RenderPass() :
			m_krLogicalDevice{ *oi.pLogicalDevice }
		{
			// color attachment description
			VkAttachmentDescription colorAttachment = {};
			colorAttachment.format = oi.pSwapChain->m_imageFormat;
			colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;

			colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;

			colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

			colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

			// how does the subpass reference our attachment
			VkAttachmentReference colorAttachmentRef = {};
			colorAttachmentRef.attachment = 0;
			colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

			// depth attachement description
			VkAttachmentDescription depthAttachment = {};
			depthAttachment.format = find_depth_format();
			depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
			depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
			depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
			depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
			depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

			// subpass depth reference
			VkAttachmentReference depthAttachmentRef{};
			depthAttachmentRef.attachment = 1;
			depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

			// actual subpass
			VkSubpassDescription subpass = {};
			subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
			// directly reference by fragment shader with layout(location = 0) out ...
			subpass.colorAttachmentCount = 1;
			subpass.pColorAttachments = &colorAttachmentRef;
			subpass.pDepthStencilAttachment = &depthAttachmentRef;

			// subpass dependencies
			VkSubpassDependency dependency = {};
			dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
			dependency.dstSubpass = 0;
			
			dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
			dependency.srcAccessMask = 0;
			
			dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
			dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

			// all attachments
			std::array<VkAttachmentDescription, 2> attachments = { colorAttachment, depthAttachment };

			// actually create the render pass
			VkRenderPassCreateInfo renderPassInfo = {};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
			renderPassInfo.pAttachments = attachments.data();
			renderPassInfo.subpassCount = 1;
			renderPassInfo.pSubpasses = &subpass;
			// including the dependencies
			renderPassInfo.dependencyCount = 1;
			renderPassInfo.pDependencies = &dependency;

			VkResult res = vkCreateRenderPass(oi.pLogicalDevice->m_device, &renderPassInfo, nullptr, &m_renderPass);
			if (res != VK_SUCCESS)
				throw std::runtime_error("Failed to create Render Pass");
		}
		RenderPass::~RenderPass()
		{
			vkDestroyRenderPass(m_krLogicalDevice.m_device, m_renderPass, nullptr);
		}

		void RenderPass::begin(const uint32_t a_kImageIndex)
		{
			VkRenderPassBeginInfo beginInfo = {};
			beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			beginInfo.renderPass = m_renderPass;
			beginInfo.framebuffer = oi.pFramebufferHandler->get(a_kImageIndex).m_framebuffer;
		
			beginInfo.renderArea.offset = { 0, 0 };
			beginInfo.renderArea.extent = oi.pSwapChain->m_extent;
			
			std::array<VkClearValue, 2> clearValues = {};
			clearValues[0].color = { { 0.0f, 0.0f, 0.0f, 1.0f } };
			clearValues[1].depthStencil = { 1.0f, 0 };

			beginInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			beginInfo.pClearValues = clearValues.data();
			
			vkCmdBeginRenderPass(oi.pCommandBuffer->m_commandBuffer, &beginInfo, VK_SUBPASS_CONTENTS_INLINE);
		}

	} // namespace vulkan

} // namespace dragonbyte_engine