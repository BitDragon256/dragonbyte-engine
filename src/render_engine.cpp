#include "render_engine.h"

#include <iostream>
#include <stdexcept>

#include <GLFW/glfw3.h>

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

namespace dragonbyte_engine
{

	RenderEngine::RenderEngine(const RenderEngineConfig& a_kConfig) :
		m_config(a_kConfig)
	{
		m_vkObjectInfo.reset();

		create_window();

		setup_vulkan();
	}
	RenderEngine::~RenderEngine()
	{
		vkWaitForFences(m_vkObjectInfo.pLogicalDevice->m_device, 1, &m_vkObjectInfo.pSyncHandler->m_inFlightFence, VK_TRUE, UINT64_MAX);
	
		m_vkObjectInfo.pRenderPass.reset();
		m_vkObjectInfo.pCommandBuffer.reset();
		m_vkObjectInfo.pCommandPool.reset();
		m_vkObjectInfo.pSyncHandler.reset();
		m_vkObjectInfo.pGraphicsPipeline.reset();
		m_vkObjectInfo.pFramebufferHandler.reset();
		m_vkObjectInfo.pSwapChain.reset();
		m_vkObjectInfo.pLogicalDevice.reset();
		m_vkObjectInfo.pPhysicalDevice.reset();
		m_vkObjectInfo.pSurface.reset();
		
		if (vulkan::validation_layers::kEnable)
			m_vkObjectInfo.pDebugMessenger.reset();
			
		m_vkObjectInfo.pInstance.reset();
		m_vkObjectInfo.pWindow.reset();
	}

	void RenderEngine::tick()
	{
		m_vkObjectInfo.pWindow->tick();

		draw_frame();

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
			create_graphics_pipeline();
			
			create_framebuffer();
			create_command_pool();
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

		m_vkObjectInfo.pWindow = std::make_shared<vulkan::Window>(windowConfig);
	}
	void RenderEngine::create_surface()
	{
		std::cout << "Create Surface" << '\n';

		m_vkObjectInfo.pSurface = std::make_shared<vulkan::Surface>(m_vkObjectInfo);
	}
	void RenderEngine::create_instance()
	{
		std::cout << "Create Instance" << '\n';

		m_vkObjectInfo.pInstance = std::make_shared<vulkan::Instance>(m_config.applicationName, m_config.engineName);
	}
	void RenderEngine::get_physical_device()
	{
		std::cout << "Get Physical Device" << '\n';

		m_vkObjectInfo.pPhysicalDevice = std::make_shared<vulkan::PhysicalDevice>(m_vkObjectInfo);
	}
	void RenderEngine::create_device()
	{
		std::cout << "Create Logical Device" << '\n';

		m_vkObjectInfo.pLogicalDevice = std::make_shared<vulkan::LogicalDevice>(m_vkObjectInfo);
	}
	void RenderEngine::create_swap_chain()
	{
		std::cout << "Create Swapchain" << '\n';

		m_vkObjectInfo.pSwapChain = std::make_shared<vulkan::SwapChain>(m_vkObjectInfo);
	}
	void RenderEngine::create_graphics_pipeline()
	{
		std::cout << "Create Graphics Pipeline" << '\n';

		m_vkObjectInfo.pGraphicsPipeline = std::make_shared<vulkan::GraphicsPipeline>(m_vkObjectInfo);
	}
	void RenderEngine::create_debug_messenger()
	{
		std::cout << "Create Debug Messenger" << '\n';

		m_vkObjectInfo.pDebugMessenger = std::make_shared<vulkan::DebugMessenger>(m_vkObjectInfo);
	}
	void RenderEngine::create_render_pass()
	{
		std::cout << "Create Render Pass" << '\n';

		m_vkObjectInfo.pRenderPass = std::make_shared<vulkan::RenderPass>(m_vkObjectInfo);
	}
	void RenderEngine::create_framebuffer()
	{
		std::cout << "Create Framebuffers" << '\n';

		m_vkObjectInfo.pFramebufferHandler = std::make_shared<vulkan::FramebufferHandler>(m_vkObjectInfo);
	}
	void RenderEngine::create_command_pool()
	{
		std::cout << "Create Command Pool" << '\n';
		
		m_vkObjectInfo.pCommandPool = std::make_shared<vulkan::CommandPool>(m_vkObjectInfo);
	}
	void RenderEngine::create_command_buffer()
	{
		std::cout << "Create Command Buffer" << '\n';
		
		m_vkObjectInfo.pCommandBuffer = std::make_shared<vulkan::CommandBuffer>(m_vkObjectInfo);
	}
	void RenderEngine::create_sync_objects()
	{
		std::cout << "Create Sync Objects" << '\n';
		
		m_vkObjectInfo.pSyncHandler = std::make_shared<vulkan::SyncHandler>(m_vkObjectInfo);
	}
	
	void RenderEngine::draw_frame()
	{
		vkWaitForFences(m_vkObjectInfo.pLogicalDevice->m_device, 1, &m_vkObjectInfo.pSyncHandler->m_inFlightFence, VK_TRUE, UINT64_MAX);
		vkResetFences(m_vkObjectInfo.pLogicalDevice->m_device, 1, &m_vkObjectInfo.pSyncHandler->m_inFlightFence);
	
		uint32_t imageIndex = m_vkObjectInfo.pSwapChain->acquire_next_image(m_vkObjectInfo);
		
		record_command_buffer(imageIndex);
		submit_command_buffer();
		
		present(imageIndex);
	}
	void RenderEngine::record_command_buffer(uint32_t a_imageIndex)
	{
		m_vkObjectInfo.pCommandBuffer->begin_recording(a_imageIndex);
	
		m_vkObjectInfo.pRenderPass->begin(m_vkObjectInfo, a_imageIndex);
		m_vkObjectInfo.pGraphicsPipeline->bind(m_vkObjectInfo);
		
		vkCmdDraw(m_vkObjectInfo.pCommandBuffer->m_commandBuffer, 3, 1, 0, 0);
		
		vkCmdEndRenderPass(m_vkObjectInfo.pCommandBuffer->m_commandBuffer);
		VkResult res = vkEndCommandBuffer(m_vkObjectInfo.pCommandBuffer->m_commandBuffer);
		if (res != VK_SUCCESS)
			throw std::runtime_error("Failed to record command buffer (ending)");
	}
	void RenderEngine::submit_command_buffer()
	{
		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		
		VkSemaphore waitSems[] = { m_vkObjectInfo.pSyncHandler->m_imageAvailableSemaphore };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSems;
		submitInfo.pWaitDstStageMask = waitStages;
		
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &m_vkObjectInfo.pCommandBuffer->m_commandBuffer;
		
		VkSemaphore signalSems[] = { m_vkObjectInfo.pSyncHandler->m_renderFinishedSemaphore };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSems;
		
		VkResult res = vkQueueSubmit(m_vkObjectInfo.pLogicalDevice->m_graphicsQueue, 1, &submitInfo, m_vkObjectInfo.pSyncHandler->m_inFlightFence);
		if (res != VK_SUCCESS)
			throw std::runtime_error("Failed to submit Draw Command Buffer");
	}
	void RenderEngine::present(uint32_t a_imageIndex)
	{
		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		
		VkSemaphore signalSems[] = { m_vkObjectInfo.pSyncHandler->m_renderFinishedSemaphore };
		
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSems;
		
		VkSwapchainKHR swapChains[] = { m_vkObjectInfo.pSwapChain->m_swapChain };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;
		presentInfo.pImageIndices = &a_imageIndex;
		
		presentInfo.pResults = nullptr;
		
		vkQueuePresentKHR(m_vkObjectInfo.pLogicalDevice->m_presentQueue, &presentInfo);
	}
	
	bool RenderEngine::should_close_window()
	{
		return m_vkObjectInfo.pWindow->should_close();
	}

} // namespace dragonbyte_engine