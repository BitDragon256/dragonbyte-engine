#pragma once

namespace dragonbyte_engine
{
	class Engine
	{
	public:
		Engine()
		{
			initialize();
		}
		~Engine()
		{
			destruct();
		}

		// disable copy constructor
		Engine(const Engine&) = delete;
		Engine& operator= (Engine&) = delete;

		virtual void initialize() = 0;
		virtual void tick() = 0;
		virtual void destruct() = 0;
	};

} // namespace dragonbyte_engine