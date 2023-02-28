#include "overseer.h"

#include <iostream>

#include "game_clock.h"
#include "dragonbyte_engine.h"
#include "object_engine.h"
#include "physics_engine.h"
#include "render_engine.h"
#include "mathematics.h"
#include "game_object.h"
#include "default_components/camera.h"

namespace dragonbyte_engine
{
	/*
	* ---------------------------------------------------------
	*						con- / destructor
	* ---------------------------------------------------------
	*/

	Overseer::Overseer()
	{

	}
	Overseer::~Overseer()
	{
		
	}
	

	/*
	* ---------------------------------------------------------
	*						game outline
	* ---------------------------------------------------------
	*/

	// called from outside to start up / represents the whole game cycle
	void Overseer::run_game()
	{
		std::cerr << "Loop Start" << '\n';
		game_loop();
		std::cerr << "Loop End" << '\n';

		std::cerr << "Ending" << '\n';
		end_game();
		std::cerr << "Ended" << '\n';
	}

	// initializes all pieces of the game engine and starts them up
	void Overseer::init_game(EngineConfig a_config)
	{
		GameClockConfig clockConfig = {};
		clockConfig.physicsFps = 50.f;
		clockConfig.targetFps = a_config.targetFps;

		m_gameClock.create(clockConfig);

		// TODO initialize File Engine
		m_fileEngine.create();

		// TODO initialize Object Engine
		m_objectEngine.create();

		// initialize Physics Engine
		m_physicsEngine.create();

		// initialize Render Engine
		RenderEngineConfig renderEngineConfig {};
		renderEngineConfig.applicationName = "Hello World";
		renderEngineConfig.engineName = "Dragonbyte Engine";
		renderEngineConfig.renderModels = true;
		renderEngineConfig.renderParticles = true;
		renderEngineConfig.renderGui = true;
		renderEngineConfig.renderType = RenderType::Rasterization;
		renderEngineConfig.windowHeight = a_config.window.height;
		renderEngineConfig.windowWidth = a_config.window.width;

		m_renderEngine.create(renderEngineConfig);

		// initialize other engines
		m_aiEngine.create();
		m_audioEngine.create();
		m_inputEngine.create(vulkan::oi.pWindow->m_pGlfwWindow);

		additional_changes(a_config);
	}
	void Overseer::additional_changes(EngineConfig a_config)
	{
		if (a_config.useDefaultCamera)
		{
			std::cout << "Setting up Default Camera\n";
			auto& cam = OBJECT_ENGINE.add_game_object("Camera");
			cam.add_component<Camera>();
			RENDER_ENGINE.set_camera(cam.get_component<Camera>());
			RENDER_ENGINE.cam_free_move(true);
		}
	}

	// destructs all pieces of the game / controlled shutdown
	void Overseer::end_game()
	{
		
	}
	void Overseer::game_loop()
	{
		std::cout << "Starting game loop..." << '\n';
		while (!should_end_game())
		{
			m_gameClock.game_loop_tick();
		}
	}

	/*
	* ---------------------------------------------------------
	*						tick methods
	* ---------------------------------------------------------
	*/

	void Overseer::pre_tick()
	{
		
	}
	void Overseer::physics_tick()
	{
		m_physicsEngine.tick();
		m_objectEngine.fixed_tick();
	}
	void Overseer::tick()
	{
		m_objectEngine.tick();
		m_inputEngine.tick();
	}
	void Overseer::render_tick()
	{
		m_renderEngine.tick();
	}
	void Overseer::late_tick()
	{
		// m_pRenderEngine->render_gui();
	}

	bool Overseer::should_end_game()
	{
		return m_renderEngine.should_close_window();
	}

	/* Overseer static global Object */
	Overseer Overseer::s_overseer;

} // namespace dragonbyte_engine