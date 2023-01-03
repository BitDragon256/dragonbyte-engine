#include "overseer.h"

#include "game_clock.h"

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
		end_game();
	}
	

	/*
	* ---------------------------------------------------------
	*						game outline
	* ---------------------------------------------------------
	*/

	// called from outside to start up / represents the whole game cycle
	void Overseer::run_game()
	{
		init_game();
		game_loop();
		end_game();
	}

	// initializes all pieces of the game engine and starts them up
	void Overseer::init_game()
	{
		GameClockConfig clockConfig;
		clockConfig.physicsFps = 50.f;
		clockConfig.targetFps = 100000.f;
		clockConfig.pOverseer = this;

		m_pGameClock = new GameClock(clockConfig);
	}

	// destructs all pieces of the game / controlled shutdown
	void Overseer::end_game()
	{
		delete m_pGameClock;
	}
	void Overseer::game_loop()
	{
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