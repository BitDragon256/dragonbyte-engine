#pragma once

#include "engines.h"

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
	class GameClock;

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


		// start game
		void run_game();

		// tick functions
		void pre_tick();
		void physics_tick();
		void tick();
		void render_tick();
		void late_tick();

	private:

		// game loop
		GameClock* m_pGameClock;

		void init_game();
		void game_loop();
		void end_game();

		bool should_end_game();

	};
} // namespace dragonbyte_engine