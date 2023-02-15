#pragma once

#include <string>

namespace dragonbyte_engine
{

	class GameObject;

	class Scene
	{
	public:
		Scene();

		GameObject& add_object(std::string name);
		GameObject& add_object(GameObject object);
	};

} // namespace dragonbyte_engine