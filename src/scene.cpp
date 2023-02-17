#include "scene.h"

#include "game_object.h"
#include "overseer.h"
#include "object_engine.h"

namespace dragonbyte_engine
{

	Scene::Scene() :
		m_root{ }
	{

	}

	GameObject_ptr Scene::add_object(std::string name)
	{
		GameObject_ptr obj = m_pOverseer->m_pObjectEngine->add_game_object(name);
		m_root.add_child(&obj->m_transform);
	}

} // namespace dragonbyte_engine