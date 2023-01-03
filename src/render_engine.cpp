#include "render_engine.h"

namespace dragonbyte_engine
{

	RenderEngine::RenderEngine(const RenderEngineConfig& config) :
		m_config(config)
	{

	}

	void RenderEngine::tick()
	{
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

	void RenderEngine::initialize()
	{
		create_window();

		create_vk_instance();
		get_physical_device();
		create_device();
		get_surface();

		create_swapchain();
	}

	void RenderEngine::create_window()
	{
		m_window = new graphics::Window();
	}

} // namespace dragonbyte_engine