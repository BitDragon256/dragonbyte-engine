#include "game_clock.h"

#include <iostream>

#include "overseer.h"

namespace dragonbyte_engine
{
	GameClock::GameClock() {}

	void GameClock::create(const GameClockConfig& config)
	{
		m_physicsDeltaTime = 1.f / config.physicsFps;
		m_targetDeltaTime = 1.f / config.targetFps;
		m_deltaTime = 0;
		m_lag = 0;
		m_firstLoop = true;
	}
	void GameClock::game_loop_tick()
	{
		OVERSEER.pre_tick();

		auto currentTime = std::chrono::high_resolution_clock::now();
		if (m_firstLoop)
		{
			m_firstLoop = false;
			m_lastTime = currentTime;
		}
		m_deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - m_lastTime).count();
		m_lastTime = currentTime;

		// std::cout << 1 / m_deltaTime << '\n';

		m_lag += m_deltaTime;

		if (m_lag < m_targetDeltaTime)
			return;

		while (m_lag > m_physicsDeltaTime)
		{
			OVERSEER.physics_tick();

			m_lag -= m_physicsDeltaTime;
		}
		
		OVERSEER.tick();
		OVERSEER.render_tick();
		OVERSEER.late_tick();
	}
} // namespace dragonbyte_engine