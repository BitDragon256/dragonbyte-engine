#pragma once

//#include "engine.h"
//#include "dragonbyte_engine.h"

#include "physics_engine.h"
#include "render_engine.h"
#include "object_engine.h"
#include "ai_engine.h"
#include "file_engine.h"
#include "audio_engine.h"
#include "input_engine.h"

#include "game_clock.h"

namespace dragonbyte_engine
{	

	struct EngineConfig;

	class Overseer
	{
	public:
		Overseer();
		~Overseer();

		// main engines
		PhysicsEngine m_physicsEngine;
		RenderEngine m_renderEngine;
		ObjectEngine m_objectEngine;

		// side engines
		AiEngine m_aiEngine;
		FileEngine m_fileEngine;
		AudioEngine m_audioEngine;
		InputEngine m_inputEngine;

		// init game
		void init_game(EngineConfig config);
		
		// start game
		void run_game();

		// tick functions
		void pre_tick();
		void physics_tick();
		void tick();
		void render_tick();
		void late_tick();

		static Overseer s_overseer;
		GameClock m_gameClock;

	private:

		// game loop
		void game_loop();
		void end_game();

		bool should_end_game();

	};

#define OVERSEER Overseer::s_overseer
#define RENDER_ENGINE OVERSEER.m_renderEngine
#define OBJECT_ENGINE OVERSEER.m_objectEngine
#define PHYSICS_ENGINE OVERSEER.m_physicsEngine
#define GAME_CLOCK OVERSEER.m_gameClock
#define INPUT OVERSEER.m_inputEngine

} // namespace dragonbyte_engine