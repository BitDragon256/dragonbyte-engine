#pragma once

#include <string>
#include <vector>

#include "ptr_types.h"
#include "component.h"
#include "scene.h"

namespace dragonbyte_engine
{

	class GameObject;
	class Transform;
	class Mesh;

	class ObjectEngine
	{
	public:
		void tick();

		void fixed_tick();
		
		Scene root;
		std::vector<GameObject> m_gameObjects;

		size_t get_mesh_count();
		void get_meshes(Mesh** meshes);
		GameObject_ptr add_game_object(std::string name);

	};

} // namespace dragonbyte_engine