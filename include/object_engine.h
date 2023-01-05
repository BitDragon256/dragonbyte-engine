#pragma once

#include "engine.h"

namespace dragonbyte_engine
{

	class ObjectEngine : Engine
	{
	public:
		void tick() override;

		void fixed_tick();

	};

} // namespace dragonbyte_engine