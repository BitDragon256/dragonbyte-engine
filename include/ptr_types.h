#pragma once

#include <memory>

namespace dragonbyte_engine
{
	class Scene;
	class GameObject;

	typedef std::unique_ptr<GameObject> GameObject_ptr;
	typedef std::unique_ptr<Scene> Scene_ptr;
	
	GameObject_ptr get_ptr(GameObject& rGameObject);
	Scene_ptr get_ptr(Scene& rScene);

} // namespace dragonbyte_engine