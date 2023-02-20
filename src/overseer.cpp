#include "overseer.h"

#include <iostream>

#include "game_clock.h"
#include "dragonbyte_engine.h"
#include "object_engine.h"
#include "physics_engine.h"
#include "render_engine.h"
#include "mathematics.h"

namespace dragonbyte_engine
{
	/*
	* ---------------------------------------------------------
	*						con- / destructor
	* ---------------------------------------------------------
	*/

	Overseer::Overseer() : 
		m_pGameClock{ nullptr }
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
		clockConfig.pOverseer = this;

		m_pGameClock = new GameClock(clockConfig);

		// TODO initialize File Engine
		m_pFileEngine = new FileEngine{  };

		// TODO initialize Object Engine
		m_pObjectEngine = new ObjectEngine{ *this };

		// initialize Physics Engine
		m_pPhysicsEngine = new PhysicsEngine{  };

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

		m_pRenderEngine = new RenderEngine(renderEngineConfig);

		// initialize other engines
		m_pAiEngine = new AiEngine();
		m_pAudioEngine = new AudioEngine();
		m_pInputEngine = new InputEngine();
	}

	// destructs all pieces of the game / controlled shutdown
	void Overseer::end_game()
	{
		delete m_pRenderEngine;
		delete m_pPhysicsEngine;
		delete m_pObjectEngine;

		delete m_pAiEngine;
		delete m_pAudioEngine;
		delete m_pFileEngine;
		delete m_pInputEngine;

		delete m_pGameClock;
	}
	void Overseer::game_loop()
	{
		std::cout << "Starting game loop..." << '\n';
		while (!should_end_game())
		{
			m_pGameClock->game_loop_tick();
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
		m_pPhysicsEngine->tick();
		m_pObjectEngine->fixed_tick();
	}
	void Overseer::tick()
	{
		m_pObjectEngine->tick();
	}
	void Overseer::render_tick()
	{
		m_pRenderEngine->tick();
	}
	void Overseer::late_tick()
	{
		// m_pRenderEngine->render_gui();
	}

	bool Overseer::should_end_game()
	{
		return m_pRenderEngine->should_close_window();
	}

} // namespace dragonbyte_engine