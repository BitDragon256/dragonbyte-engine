#pragma once

#include <string>
#include "game_object.h"
#include "ptr_types.h"

namespace dragonbyte_engine
{

	class GameObject;

	class Scene
	{
	public:
		Scene();

		GameObject& add_object(std::string name);
		GameObject& add_object(GameObject object);

	private:
		TransformNode m_root;
	};

} // namespace dragonbyte_engine