#include "render_engine.h"

#include <chrono>
#include <iostream>
#include <stdexcept>

#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "tools.h"
#include "vulkan/validation_layers.h"
#include "vulkan/object_info.h"

#include "vulkan/window.h"
#include "vulkan/instance.h"
#include "vulkan/debug_messenger.h"
#include "vulkan/surface.h"
#include "vulkan/physical_device.h"
#include "vulkan/logical_device.h"
#include "vulkan/swapchain.h"
#include "vulkan/render_pass.h"
#include "vulkan/graphics_pipeline.h"
#include "vulkan/framebuffer.h"
#include "vulkan/command_pool.h"
#include "vulkan/command_buffer.h"
#include "vulkan/sync_handler.h"
#include "vulkan/vertex_buffer.h"
#include "vulkan/index_buffer.h"
#include "vulkan/uniform_buffer_handler.h"
#include "vulkan/descriptor_set_handler.h"
#include "vulkan/descriptor_pool.h"
#include "vulkan/depth_handler.h"

namespace dragonbyte_engine
{	

	RenderEngine::RenderEngine(const RenderEngineConfig& a_kConfig) :
		m_config(a_kConfig)
	{
		vulkan::oi.reset();

		create_window();

		setup_vulkan();
	}
	RenderEngine::~RenderEngine()
	{
		vkWaitForFences(vulkan::oi.pLogicalDevice->m_device, 1, &vulkan::oi.pSyncHandler->m_inFlightFence, VK_TRUE, UINT64_MAX);
	
		std::cout << "Starting destruction" <<'\n';
		
		vulkan::oi.pVertexBuffer.reset();
		vulkan::oi.pIndexBuffer.reset();
		
		vulkan::oi.pRenderPass.reset();
		vulkan::oi.pCommandBuffer.reset();
		vulkan::oi.pCommandPoolHandler.reset();
		vulkan::oi.pSyncHandler.reset();
		vulkan::oi.pGraphicsPipeline.reset();
		vulkan::oi.pFramebufferHandler.reset();
		vulkan::oi.pDepthHandler.reset();
		vulkan::oi.pSwapChain.reset();

		vulkan::oi.pUniformBufferHandler.reset();
		vulkan::oi.pDescriptorPool.reset();
		vulkan::oi.pDescriptorSetHandler.reset();
		
		vulkan::oi.pLogicalDevice.reset();
		vulkan::oi.pPhysicalDevice.reset();
		vulkan::oi.pSurface.reset();
		
		if (vulkan::validation_layers::kEnable)
			vulkan::oi.pDebugMessenger.reset();
			
		vulkan::oi.pInstance.reset();
		vulkan::oi.pWindow.reset();
	}

	void RenderEngine::tick()
	{
		vulkan::oi.pWindow->tick();

		draw_frame();

		vulkan::oi.pVertexBuffer->reload();

		// render_models();
		// render_particles();
		// render_gui();
	}
	void RenderEngine::render_models()
	{
		if (!m_config.renderModels)
			return;
			
		
	}
	void RenderEngine::render_particles()
	{
		if (!m_config.renderParticles)
			return;
	}
	void RenderEngine::render_gui()
	{
		if (!m_config.renderGui)
			return;
	}

	void RenderEngine::setup_vulkan()
	{
		std::cout << "Setting up Vulkan..." << '\n';

		try
		{
			create_instance();
			if (vulkan::validation_layers::kEnable)
				create_debug_messenger();
			create_surface();

			get_physical_device();
			create_device();

			create_swap_chain();
			create_render_pass();
			create_descriptor_set_layout();
			create_graphics_pipeline();
			
			create_depth_handler();
			create_framebuffer();
			create_command_pool_handler();
			
			create_allocator();

			create_vertex_buffer();
			create_index_buffer();
			create_uniform_buffer_handler();
			create_descriptor_pool();
			create_descriptor_set_handler();

			create_command_buffer();
			
			create_sync_objects();
		}
		catch (const std::exception& e)
		{
			tools::print_error(e);
			exit(EXIT_FAILURE);
		}

		std::cout << "Finished setting up Vulkan..." << '\n';
	}
	void RenderEngine::create_window()
	{
		std::cout << "Create Window" << '\n';

		vulkan::WindowConfig windowConfig{};
		windowConfig.height = m_config.windowHeight;
		windowConfig.width = m_config.windowWidth;
		windowConfig.name = m_config.applicationName;

		vulkan::oi.pWindow = std::make_shared<vulkan::Window>(windowConfig);
	}
	void RenderEngine::create_surface()
	{
		std::cout << "Create Surface" << '\n';

		vulkan::oi.pSurface = std::make_shared<vulkan::Surface>();
	}
	void RenderEngine::create_instance()
	{
		std::cout << "Create Instance" << '\n';

		vulkan::oi.pInstance = std::make_shared<vulkan::Instance>(m_config.applicationName, m_config.engineName);
	}
	void RenderEngine::get_physical_device()
	{
		std::cout << "Get Physical Device" << '\n';

		vulkan::oi.pPhysicalDevice = std::make_shared<vulkan::PhysicalDevice>();
	}
	void RenderEngine::create_device()
	{
		std::cout << "Create Logical Device" << '\n';

		vulkan::oi.pLogicalDevice = std::make_shared<vulkan::LogicalDevice>();
	}
	void RenderEngine::create_swap_chain()
	{
		std::cout << "Create Swapchain" << '\n';

		vulkan::oi.pSwapChain = std::make_shared<vulkan::SwapChain>();
	}
	void RenderEngine::create_graphics_pipeline()
	{
		std::cout << "Create Graphics Pipeline" << '\n';

		vulkan::oi.pGraphicsPipeline = std::make_shared<vulkan::GraphicsPipeline>();
	}
	void RenderEngine::create_debug_messenger()
	{
		std::cout << "Create Debug Messenger" << '\n';

		vulkan::oi.pDebugMessenger = std::make_shared<vulkan::DebugMessenger>();
	}
	void RenderEngine::create_render_pass()
	{
		std::cout << "Create Render Pass" << '\n';

		vulkan::oi.pRenderPass = std::make_shared<vulkan::RenderPass>();
	}
	void RenderEngine::create_framebuffer()
	{
		std::cout << "Create Framebuffers" << '\n';

		vulkan::oi.pFramebufferHandler = std::make_shared<vulkan::FramebufferHandler>();
	}
	void RenderEngine::create_command_pool_handler()
	{
		std::cout << "Create Command Pool Handler" << '\n';
		
		vulkan::oi.pCommandPoolHandler = std::make_shared<vulkan::CommandPoolHandler>();
	}
	void RenderEngine::create_command_buffer()
	{
		std::cout << "Create Command Buffer" << '\n';
		
		vulkan::oi.pCommandBuffer = std::make_shared<vulkan::CommandBuffer>(vulkan::CommandPoolQueueType::Graphics);
	}
	void RenderEngine::create_sync_objects()
	{
		std::cout << "Create Sync Objects" << '\n';
		
		vulkan::oi.pSyncHandler = std::make_shared<vulkan::SyncHandler>();
	}
	void RenderEngine::create_vertex_buffer()
	{
		std::cout << "Create Vertex Buffer" << '\n';
		
		vulkan::oi.pVertexBuffer = std::make_shared<vulkan::VertexBuffer>();
	}
	void RenderEngine::create_index_buffer()
	{
		std::cout << "Create Index Buffer" << '\n';

		vulkan::oi.pIndexBuffer = std::make_shared<vulkan::IndexBuffer>();
	}
	void RenderEngine::create_allocator()
	{
		std::cout << "Create VMA Allocator" << '\n';
		
		vulkan::oi.pAllocator = std::make_shared<vulkan::Allocator>();
	}
	void RenderEngine::create_descriptor_set_handler()
	{
		std::cout << "Create Descriptor Set" << '\n';

		vulkan::oi.pDescriptorSetHandler->create();
	}
	void RenderEngine::create_uniform_buffer_handler()
	{
		std::cout << "Create Uniform Buffer Handler" << '\n';
		
		vulkan::oi.pUniformBufferHandler = std::make_shared<vulkan::UniformBufferHandler>();
	}
	void RenderEngine::create_descriptor_pool()
	{
		std::cout << "Create Descriptor Pool" << '\n';

		vulkan::oi.pDescriptorPool = std::make_shared<vulkan::DescriptorPool>();
	}
	void RenderEngine::create_descriptor_set_layout()
	{
		std::cout << "Create Descriptor Set Layout" << '\n';

		vulkan::oi.pDescriptorSetHandler = std::make_shared<vulkan::DescriptorSetHandler>();
		vulkan::oi.pDescriptorSetHandler->create_descriptor_set();
	}
	void RenderEngine::create_depth_handler()
	{
		std::cout << "Create Depth Handler" << '\n';

		vulkan::oi.pDepthHandler = std::make_shared<vulkan::DepthHandler>();
	}
	
	void RenderEngine::draw_frame()
	{
		vkWaitForFences(vulkan::oi.pLogicalDevice->m_device, 1, &vulkan::oi.pSyncHandler->m_inFlightFence, VK_TRUE, UINT64_MAX);
		vkResetFences(vulkan::oi.pLogicalDevice->m_device, 1, &vulkan::oi.pSyncHandler->m_inFlightFence);
	
		uint32_t imageIndex = vulkan::oi.pSwapChain->acquire_next_image();

		update_uniform_buffer_handler(imageIndex);
		
		record_command_buffer(imageIndex);
		submit_command_buffer();
		
		present(imageIndex);
	}
	void RenderEngine::update_uniform_buffer_handler(uint32_t a_currentImage)
	{
		static auto startTime = std::chrono::high_resolution_clock::now();

		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

		vulkan::UniformBufferObject ubo = {};
		ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));
		ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.proj = glm::perspective(glm::radians(45.0f), vulkan::oi.pSwapChain->m_extent.width / (float)vulkan::oi.pSwapChain->m_extent.height, 0.1f, 10.0f);
		ubo.proj[1][1] *= -1;

		vulkan::oi.pUniformBufferHandler->push_data(a_currentImage, ubo);
	}
	void RenderEngine::record_command_buffer(uint32_t a_imageIndex)
	{
		vulkan::oi.pCommandBuffer->begin_recording(a_imageIndex);
	
		vulkan::oi.pRenderPass->begin(a_imageIndex);
		vulkan::oi.pGraphicsPipeline->bind();
		
		vulkan::oi.pVertexBuffer->bind();
		vulkan::oi.pIndexBuffer->bind();

		vulkan::oi.pDescriptorSetHandler->bind(a_imageIndex);

		// vkCmdDraw(vulkan::oi.pCommandBuffer->m_commandBuffer, static_cast<uint32_t>(vulkan::oi.pVertexBuffer->m_vertices.size()), 1, 0, 0);
		vkCmdDrawIndexed(vulkan::oi.pCommandBuffer->m_commandBuffer, static_cast<uint32_t>(vulkan::oi.pIndexBuffer->m_indices.size()), 1, 0, 0, 0);
		
		vkCmdEndRenderPass(vulkan::oi.pCommandBuffer->m_commandBuffer);
		VkResult res = vkEndCommandBuffer(vulkan::oi.pCommandBuffer->m_commandBuffer);
		if (res != VK_SUCCESS)
			throw std::runtime_error("Failed to record command buffer (ending)");
	}
	void RenderEngine::submit_command_buffer()
	{
		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		
		VkSemaphore waitSems[] = { vulkan::oi.pSyncHandler->m_imageAvailableSemaphore };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSems;
		submitInfo.pWaitDstStageMask = waitStages;
		
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &vulkan::oi.pCommandBuffer->m_commandBuffer;
		
		VkSemaphore signalSems[] = { vulkan::oi.pSyncHandler->m_renderFinishedSemaphore };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSems;
		
		VkResult res = vkQueueSubmit(vulkan::oi.pLogicalDevice->m_graphicsQueue, 1, &submitInfo, vulkan::oi.pSyncHandler->m_inFlightFence);
		if (res != VK_SUCCESS)
			throw std::runtime_error("Failed to submit Draw Command Buffer");
	}
	void RenderEngine::present(uint32_t a_imageIndex)
	{
		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		
		VkSemaphore signalSems[] = { vulkan::oi.pSyncHandler->m_renderFinishedSemaphore };
		
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSems;
		
		VkSwapchainKHR swapChains[] = { vulkan::oi.pSwapChain->m_swapChain };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;
		presentInfo.pImageIndices = &a_imageIndex;
		
		presentInfo.pResults = nullptr;
		
		vkQueuePresentKHR(vulkan::oi.pLogicalDevice->m_presentQueue, &presentInfo);
	}
	
	bool RenderEngine::should_close_window()
	{
		return vulkan::oi.pWindow->should_close();
	}

} // namespace dragonbyte_engine