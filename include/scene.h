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
		Scene(Overseer& rOverseer);

		GameObject& add_object(std::string name);
		GameObject& add_object(GameObject object);

	private:
		TransformNode m_root;
		Overseer* m_pOverseer;
	};

} // namespace dragonbyte_engine