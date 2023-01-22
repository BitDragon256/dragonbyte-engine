#include "vulkan/graphics_pipeline.h"

#include <stdexcept>

#include "vulkan/object_info.h"

#include "vulkan/command_buffer.h"
#include "vulkan/render_pass.h"
#include "vulkan/swapchain.h"
#include "vulkan/vertex.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		GraphicsPipeline::GraphicsPipeline(const ObjectInfo& a_krObjectInfo) :
			m_krLogicalDevice{ *a_krObjectInfo.pLogicalDevice }
		{
			// create the shader modules
			m_pVertShaderModule = new ShaderModule(
				default_shaders::get_shader_filename(default_shaders::eShader::Simple, default_shaders::eShaderType::Vert),
				a_krObjectInfo
			);
			m_pFragShaderModule = new ShaderModule(
				default_shaders::get_shader_filename(default_shaders::eShader::Simple, default_shaders::eShaderType::Frag),
				a_krObjectInfo
			);

			// create infos for later staging the shader modules
			VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
			vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
			vertShaderStageInfo.module = m_pVertShaderModule->m_shaderModule;
			vertShaderStageInfo.pName = "main";

			VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
			fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
			fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
			fragShaderStageInfo.module = m_pFragShaderModule->m_shaderModule;
			fragShaderStageInfo.pName = "main";

			// combine both
			VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

			/* ------------------------------------------
			*					Vertices
			*  ------------------------------------------
			*/


			// dynamic states for being able to change some stuff at runtime
			std::vector<VkDynamicState> dynamicStates = {
				VK_DYNAMIC_STATE_VIEWPORT,
				VK_DYNAMIC_STATE_SCISSOR
			};

			VkPipelineDynamicStateCreateInfo dynamicState = {};
			dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
			dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
			dynamicState.pDynamicStates = dynamicStates.data();

			// vertex input stuff
			auto bindingDescription = Vertex::get_binding_desc();
			auto attributeDescriptions = Vertex::get_attribute_desc();
			
			VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
			vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
			vertexInputInfo.vertexBindingDescriptionCount = 1;
			vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
			vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
			vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

			// vertex assembly stuff
			VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
			inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
			inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			inputAssembly.primitiveRestartEnable = VK_FALSE;

			// viewport
			VkViewport viewport{};
			viewport.x = 0.0f;
			viewport.y = 0.0f;
			
			viewport.width = (float) a_krObjectInfo.pSwapChain->m_extent.width;
			viewport.height = (float) a_krObjectInfo.pSwapChain->m_extent.height;
			viewport.minDepth = 0.0f;
			viewport.maxDepth = 1.0f;

			// scissor
			VkRect2D scissor{};
			scissor.offset = { 0, 0 };
			scissor.extent = a_krObjectInfo.pSwapChain->m_extent;

			// combine viewport and scissor
			VkPipelineViewportStateCreateInfo viewportState = {};
			viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
			viewportState.viewportCount = 1;
			viewportState.scissorCount = 1;


			/* ------------------------------------------
			*				Rasterization
			*  ------------------------------------------
			*/

			// rasterization settings
			VkPipelineRasterizationStateCreateInfo rasterizer = {};
			rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;

			rasterizer.depthClampEnable = VK_FALSE;
			rasterizer.rasterizerDiscardEnable = VK_FALSE;

			rasterizer.polygonMode = VK_POLYGON_MODE_FILL;

			rasterizer.lineWidth = 1.0f;

			rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
			rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;

			rasterizer.depthBiasEnable = VK_FALSE;
			rasterizer.depthBiasConstantFactor = 0.0f; // Optional
			rasterizer.depthBiasClamp = 0.0f; // Optional
			rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

			// multisampling
			VkPipelineMultisampleStateCreateInfo multisampling = {};
			multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
			multisampling.sampleShadingEnable = VK_FALSE;
			multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
			multisampling.minSampleShading = 1.0f; // Optional
			multisampling.pSampleMask = nullptr; // Optional
			multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
			multisampling.alphaToOneEnable = VK_FALSE; // Optional

			// color blending
			VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
			colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
			colorBlendAttachment.blendEnable = VK_FALSE;
			colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
			colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
			colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
			colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
			colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
			colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

			// alpha blending
			/*colorBlendAttachment.blendEnable = VK_TRUE;
			colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
			colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
			colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
			colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;*/

			VkPipelineColorBlendStateCreateInfo colorBlending = {};
			colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
			colorBlending.logicOpEnable = VK_FALSE;
			colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
			colorBlending.attachmentCount = 1;
			colorBlending.pAttachments = &colorBlendAttachment;
			colorBlending.blendConstants[0] = 0.0f; // Optional
			colorBlending.blendConstants[1] = 0.0f; // Optional
			colorBlending.blendConstants[2] = 0.0f; // Optional
			colorBlending.blendConstants[3] = 0.0f; // Optional


			/* ------------------------------------------
			*				  Creation
			*  ------------------------------------------
			*/

			// pipeline layout creation
			VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
			pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			pipelineLayoutInfo.setLayoutCount = 0; // Optional
			pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
			pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
			pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

			VkResult res = vkCreatePipelineLayout(a_krObjectInfo.pLogicalDevice->m_device, &pipelineLayoutInfo, nullptr, &m_pipelineLayout);
			if (res != VK_SUCCESS)
				throw std::runtime_error("Failed to create Pipeline Layout");

			// actual pipeline creation
			VkGraphicsPipelineCreateInfo pipelineInfo = {};
			pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
			pipelineInfo.stageCount = 2;
			pipelineInfo.pStages = shaderStages;

			pipelineInfo.pVertexInputState = &vertexInputInfo;
			pipelineInfo.pInputAssemblyState = &inputAssembly;
			pipelineInfo.pViewportState = &viewportState;
			pipelineInfo.pRasterizationState = &rasterizer;
			pipelineInfo.pMultisampleState = &multisampling;
			pipelineInfo.pDepthStencilState = nullptr; // Optional
			pipelineInfo.pColorBlendState = &colorBlending;
			pipelineInfo.pDynamicState = &dynamicState;

			pipelineInfo.layout = m_pipelineLayout;

			pipelineInfo.renderPass = a_krObjectInfo.pRenderPass->m_renderPass;
			pipelineInfo.subpass = 0;

			pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
			pipelineInfo.basePipelineIndex = -1; // Optional

			res = vkCreateGraphicsPipelines(a_krObjectInfo.pLogicalDevice->m_device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_pipeline);
			if (res != VK_SUCCESS)
				throw std::runtime_error("Failed to create Graphics Pipeline");

			// destruction of the shader modules
			delete m_pFragShaderModule;
			delete m_pVertShaderModule;
		}
		GraphicsPipeline::~GraphicsPipeline()
		{
			vkDestroyPipelineLayout(m_krLogicalDevice.m_device, m_pipelineLayout, nullptr);
			vkDestroyPipeline(m_krLogicalDevice.m_device, m_pipeline, nullptr);
		}

		void GraphicsPipeline::bind(const ObjectInfo& a_krObjectInfo)
		{
			VkViewport viewport = {};
			viewport.x = 0.f;
			viewport.y = 0.f;
			viewport.width = static_cast<float>(a_krObjectInfo.pSwapChain->m_extent.width);
			viewport.height = static_cast<float>(a_krObjectInfo.pSwapChain->m_extent.height);
			viewport.minDepth = 0.f;
			viewport.maxDepth = 1.f;
			vkCmdSetViewport(a_krObjectInfo.pCommandBuffer->m_commandBuffer, 0, 1, &viewport);
			
			VkRect2D scissor = {};
			scissor.offset = { 0, 0 };
			scissor.extent = a_krObjectInfo.pSwapChain->m_extent;
			vkCmdSetScissor(a_krObjectInfo.pCommandBuffer->m_commandBuffer, 0, 1, &scissor);
			
			vkCmdBindPipeline(a_krObjectInfo.pCommandBuffer->m_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline);
		}

	} // namespace vulkan

} // namespace dragonbyte_engine