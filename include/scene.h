#pragma once

#include <string>
#include "game_object.h"
#include "ptr_types.h"

namespace dragonbyte_engine
{

	class GameObject;
	class Overseer;

	class Scene
	{
	public:
		Scene();

		GameObject_ptr add_object(std::string name);
		GameObject_ptr add_object(GameObject object);

	private:
		Transform m_root;
		Overseer* m_pOverseer;
	};

} // namespace dragonbyte_engine