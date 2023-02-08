#pragma once

#include <vector>

#include "engine.h"

namespace dragonbyte_engine
{

	class GameObject;

	class ObjectEngine : Engine
	{
	public:
		void tick() override;

		void fixed_tick();
		
		std::vector<GameObject> m_gameObjects;

	};

} // namespace dragonbyte_engine