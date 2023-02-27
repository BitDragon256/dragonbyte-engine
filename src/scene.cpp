#include "scene.h"

#include "game_object.h"
#include "overseer.h"
#include "object_engine.h"

namespace dragonbyte_engine
{

	Scene::Scene() :
		m_root{ nullptr }
	{

	}

	GameObject& Scene::add_object(std::string name)
	{
		auto& obj = OBJECT_ENGINE.add_game_object(name);
		m_root.add_child(&obj.m_transform.m_node);

		return OBJECT_ENGINE.last_game_object();
	}

} // namespace dragonbyte_engine