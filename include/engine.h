#pragma once

namespace dragonbyte_engine
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		// disable copy constructor
		Engine(const Engine&) = delete;
		Engine& operator= (Engine&) = delete;

		virtual void tick() = 0;
	};

} // namespace dragonbyte_engine