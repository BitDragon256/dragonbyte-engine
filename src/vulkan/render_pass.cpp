#include "vulkan/render_pass.h"

#include <stdexcept>

#include "vulkan/object_info.h"

#include "vulkan/swapchain.h"

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

			// actually create the render pass
			VkRenderPassCreateInfo renderPassInfo = {};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			renderPassInfo.attachmentCount = 1;
			renderPassInfo.pAttachments = &colorAttachment;
			renderPassInfo.subpassCount = 1;
			renderPassInfo.pSubpasses = &subpass;

			VkResult res = vkCreateRenderPass(a_krObjectInfo.pLogicalDevice->m_device, &renderPassInfo, nullptr, &m_renderPass);
			if (res != VK_SUCCESS)
				throw std::runtime_error("Failed to create Render Pass");
		}
		RenderPass::~RenderPass()
		{
			vkDestroyRenderPass(m_krLogicalDevice.m_device, m_renderPass, nullptr);
		}

	} // namespace vulkan

} // namespace dragonbyte_engine