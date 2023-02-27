#include "scene.h"

#include "game_object.h"
#include "overseer.h"
#include "object_engine.h"

namespace dragonbyte_engine
{

	Scene::Scene(Overseer& a_rOverseer) :
		m_root{ nullptr }, m_pOverseer{ &a_rOverseer }
	{

	}

	GameObject& Scene::add_object(std::string name)
	{
		auto& obj = m_pOverseer->m_pObjectEngine->add_game_object(name);
		m_root.add_child(&obj.m_transform.m_node);

		return m_pOverseer->m_pObjectEngine->last_game_object();
	}

} // namespace dragonbyte_engine