#pragma once

//#include "engine.h"
//#include "dragonbyte_engine.h"

//#include "physics_engine.h"
//#include "render_engine.h"
//#include "object_engine.h"
#include "ai_engine.h"
#include "file_engine.h"
#include "audio_engine.h"
#include "input_engine.h"

#include "game_clock.h"

namespace dragonbyte_engine
{
	class GameClock;

	class PhysicsEngine;
	class RenderEngine;
	class ObjectEngine;
	
	struct EngineConfig;

	class Overseer
	{
	public:
		Overseer();
		~Overseer();

		// main engines
		PhysicsEngine* m_pPhysicsEngine;
		RenderEngine* m_pRenderEngine;
		ObjectEngine* m_pObjectEngine;

		// side engines
		AiEngine* m_pAiEngine;
		FileEngine* m_pFileEngine;
		AudioEngine* m_pAudioEngine;
		InputEngine* m_pInputEngine;

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
		GameClock* m_pGameClock;

	private:

		// game loop
		void game_loop();
		void end_game();

		bool should_end_game();

	};

#define OVERSEER Overseer::s_overseer

} // namespace dragonbyte_engine