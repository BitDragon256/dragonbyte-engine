#pragma once

#include <vector>

#include "component.h"

namespace dragonbyte_engine
{

	class GameObject;
	class Transform;
	class Mesh;
	
	typedef Transform Scene;

	class ObjectEngine
	{
	public:
		void tick();

		void fixed_tick();
		
		Scene root;
		std::vector<GameObject> m_gameObjects;

		size_t get_mesh_count();
		void get_meshes(Mesh** meshes);

	};

} // namespace dragonbyte_engine