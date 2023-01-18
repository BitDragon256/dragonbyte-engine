#include "render_engine.h"

#include <iostream>
#include <stdexcept>

#include <GLFW/glfw3.h>

#include "tools.h"
#include "vulkan/validation_layers.h"
#include "vulkan/object_info.h"

#include "vulkan/debug_messenger.h"
#include "vulkan/framebuffer.h"
#include "vulkan/graphics_pipeline.h"
#include "vulkan/instance.h"
#include "vulkan/logical_device.h"
#include "vulkan/physical_device.h"
#include "vulkan/render_pass.h"
#include "vulkan/surface.h"
#include "vulkan/swapchain.h"
#include "vulkan/window.h"

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

		render_models();
		render_particles();
		render_gui();
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
		std::cout << "Create Framebuffer" << '\n';

		m_vkObjectInfo.pFramebufferHandler = std::make_shared<vulkan::FramebufferHandler>(m_vkObjectInfo);
	}

	bool RenderEngine::should_close_window()
	{
		return m_vkObjectInfo.pWindow->should_close();
	}

} // namespace dragonbyte_engine