#pragma once

#include <chrono>
#include <functional>
#include <vector>

namespace dragonbyte_engine
{
	class Tickable
	{
	public:
		virtual void start() {};

		virtual void pre_tick() {};
		virtual void physics_tick() {};
		virtual void tick() {};
		virtual void render_tick() {};
		virtual void late_tick() {};
		virtual void gui_tick() {};

		virtual void end() {};
	};

	struct GameClockConfig
	{
		float physicsFps;
		float targetFps;
	};

	class GameClock
	{
	public:

		GameClock();

		void create(const GameClockConfig& config);
		void game_loop_tick();

		float m_deltaTime;

	private:

		float m_physicsDeltaTime;
		float m_targetDeltaTime;

		float m_lag;
		bool m_firstLoop;

		std::chrono::high_resolution_clock::time_point m_time;
		std::chrono::high_resolution_clock::time_point m_lastTime;
	};

} // namespace dragonbyte_engine