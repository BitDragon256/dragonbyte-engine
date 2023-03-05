#pragma once

#include <string>
#include <vector>

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

		void create(uint32_t a_maxGameObjects);
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