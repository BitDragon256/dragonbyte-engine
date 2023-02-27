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
		ObjectEngine();

		void tick();

		void fixed_tick();
		
		Scene m_root;
		std::vector<GameObject> m_gameObjects;

		void get_meshes(std::vector<Mesh*>& rMeshes);
		void get_transforms(std::vector<Transform*>& rTransforms);
		GameObject& add_game_object(std::string name);
		GameObject& last_game_object();

	};

} // namespace dragonbyte_engine