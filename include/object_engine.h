#pragma once

#include <vector>

#include "engine.h"

#include "component.h"

namespace dragonbyte_engine
{

	class GameObject;
	class Mesh;

	class ObjectEngine : Engine
	{
	public:
		void tick() override;

		void fixed_tick();
		
		std::vector<GameObject> m_gameObjects;

		std::vector<Mesh&> get_meshes();

	};

} // namespace dragonbyte_engine