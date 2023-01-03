#pragma once

#include "engines.h"

namespace dragonbyte_engine
{

	class ObjectEngine : Engine
	{
	public:
		void initialize() override;
		void tick() override;
		void destruct() override;

		void fixed_tick();

	};

} // namespace dragonbyte_engine