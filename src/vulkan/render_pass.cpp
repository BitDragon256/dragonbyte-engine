#include "vulkan/render_pass.h"

#include <stdexcept>

#include "vulkan/object_info.h"
#include "vulkan/swapchain.h"
#include "vulkan/command_buffer.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		RenderPass::RenderPass(const ObjectInfo& a_krObjectInfo) :
			m_krLogicalDevice{ *a_krObjectInfo.pLogicalDevice }
		{
			// attachment description
			VkAttachmentDescription colorAttachment = {};
			colorAttachment.format = a_krObjectInfo.pSwapChain->m_imageFormat;
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

			// actual subpass
			VkSubpassDescription subpass = {};
			subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
			// directly reference by fragment shader with layout(location = 0) out ...
			subpass.colorAttachmentCount = 1;
			subpass.pColorAttachments = &colorAttachmentRef;

			// subpass dependencies
			VkSubpassDependency dependency = {};
			dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
			dependency.dstSubpass = 0;
			
			dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			dependency.srcAccessMask = 0;
			
			dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

			// actually create the render pass
			VkRenderPassCreateInfo renderPassInfo = {};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			renderPassInfo.attachmentCount = 1;
			renderPassInfo.pAttachments = &colorAttachment;
			renderPassInfo.subpassCount = 1;
			renderPassInfo.pSubpasses = &subpass;
			// including the dependencies
			renderPassInfo.dependencyCount = 1;
			renderPassInfo.pDependencies = &dependency;

			VkResult res = vkCreateRenderPass(a_krObjectInfo.pLogicalDevice->m_device, &renderPassInfo, nullptr, &m_renderPass);
			if (res != VK_SUCCESS)
				throw std::runtime_error("Failed to create Render Pass");
		}
		RenderPass::~RenderPass()
		{
			vkDestroyRenderPass(m_krLogicalDevice.m_device, m_renderPass, nullptr);
		}

		void RenderPass::begin(const ObjectInfo& a_krObjectInfo, const uint32_t a_kImageIndex)
		{
			VkRenderPassBeginInfo beginInfo = {};
			beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			beginInfo.renderPass = m_renderPass;
			beginInfo.framebuffer = a_krObjectInfo.pFramebufferHandler->get(a_kImageIndex).m_framebuffer;
		
			beginInfo.renderArea.offset = { 0, 0 };
			beginInfo.renderArea.extent = a_krObjectInfo.pSwapChain->m_extent;
			
			VkClearValue clearColor = {{{ 0.f, 0.f, 0.f, 1.f }}};
			beginInfo.clearValueCount = 1;
			beginInfo.pClearValues = &clearColor;
			
			vkCmdBeginRenderPass(a_krObjectInfo.pCommandBuffer->m_commandBuffer, &beginInfo, VK_SUBPASS_CONTENTS_INLINE);
		}

	} // namespace vulkan

} // namespace dragonbyte_engine