#pragma once

#include <string>
#include "game_object.h"
#include "transform.h"

namespace dragonbyte_engine
{

	class GameObject;

	class Scene
	{
	public:
		Scene();

		GameObject& add_object(std::string name);
		GameObject& add_object(GameObject object);

		void load_from_file(std::string file);

	private:
		TransformNode m_root;
	};

} // namespace dragonbyte_engine