#include "render_engine.h"

#include <stdexcept>

#include <GLFW/glfw3.h>

namespace dragonbyte_engine
{

	RenderEngine::RenderEngine(const RenderEngineConfig& a_kConfig) :
		m_config(a_kConfig)
	{
		create_window();

		create_instance();
		create_physical_device();
		create_device();
	}
	RenderEngine::~RenderEngine()
	{
		delete m_pLogicalDevice;
		delete m_pPhysicalDevice;
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

	void RenderEngine::create_window()
	{
		vulkan::WindowConfig windowConfig{};
		windowConfig.height = m_config.windowHeight;
		windowConfig.width = m_config.windowWidth;
		windowConfig.name = m_config.applicationName;

		m_pWindow = new vulkan::Window(windowConfig);
	}
	void RenderEngine::create_instance()
	{
		m_pInstance = new vulkan::Instance(m_config.applicationName, m_config.engineName);
	}
	void RenderEngine::create_physical_device()
	{
		m_pPhysicalDevice = new vulkan::PhysicalDevice(*m_pInstance);
	}
	void RenderEngine::create_device()
	{
		m_pLogicalDevice = new vulkan::LogicalDevice(*m_pPhysicalDevice);
	}

	bool RenderEngine::should_close_window()
	{
		return m_pWindow->should_close();
	}

} // namespace dragonbyte_engine