#include "render_engine.h"

#include <iostream>
#include <stdexcept>

#include <GLFW/glfw3.h>

#include "tools.h"

namespace dragonbyte_engine
{

	RenderEngine::RenderEngine(const RenderEngineConfig& a_kConfig) :
		m_config(a_kConfig)
	{
		create_window();

		setup_vulkan();
	}
	RenderEngine::~RenderEngine()
	{
		delete m_pSwapChain;
		delete m_pLogicalDevice;
		delete m_pPhysicalDevice;
		delete m_pSurface;
		delete m_pInstance;
		delete m_pWindow;
	}

	void RenderEngine::tick()
	{
		m_pWindow->tick();

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
			create_surface();

			get_physical_device();
			create_device();

			create_swap_chain();
			create_graphics_pipeline();
		}
		catch (const std::exception& e)
		{
			tools::print_error(e);
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

		m_pWindow = new vulkan::Window(windowConfig);
	}
	void RenderEngine::create_surface()
	{
		std::cout << "Create Surface" << '\n';

		m_pSurface = new vulkan::Surface(m_pInstance, m_pWindow);
	}
	void RenderEngine::create_instance()
	{
		std::cout << "Create Instance" << '\n';

		m_pInstance = new vulkan::Instance(m_config.applicationName, m_config.engineName);
	}
	void RenderEngine::get_physical_device()
	{
		std::cout << "Get Physical Device" << '\n';

		m_pPhysicalDevice = new vulkan::PhysicalDevice(*m_pInstance, *m_pSurface);
	}
	void RenderEngine::create_device()
	{
		std::cout << "Create Logical Device" << '\n';

		m_pLogicalDevice = new vulkan::LogicalDevice(*m_pPhysicalDevice);
	}
	void RenderEngine::create_swap_chain()
	{
		std::cout << "Create Swapchain" << '\n';

		m_pSwapChain = new vulkan::SwapChain(*m_pWindow, *m_pPhysicalDevice, *m_pLogicalDevice);
	}
	void RenderEngine::create_graphics_pipeline()
	{
		std::cout << "Create Graphics Pipeline" << '\n';

		m_pGraphicsPipeline = new vulkan::GraphicsPipeline(*m_pLogicalDevice);
	}

	bool RenderEngine::should_close_window()
	{
		return m_pWindow->should_close();
	}

} // namespace dragonbyte_engine