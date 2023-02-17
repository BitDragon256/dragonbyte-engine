#pragma once

#include <memory>

namespace dragonbyte_engine
{
	class GameObject;
	class Scene;

	typedef std::unique_ptr<GameObject> GameObject_ptr;
	typedef std::unique_ptr<Scene> Scene_ptr;

} // namespace dragonbyte_engine