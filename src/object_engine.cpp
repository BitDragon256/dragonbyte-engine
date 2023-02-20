#include "object_engine.h"

#include "mesh.h"

namespace dragonbyte_engine
{

	ObjectEngine::ObjectEngine(Overseer& a_rOverseer) :
		m_gameObjects{  }, m_root{ a_rOverseer }
	{
		
	}

	void ObjectEngine::tick()
	{

	}
	void ObjectEngine::fixed_tick()
	{

	}
	void ObjectEngine::get_meshes(std::vector<Mesh*>& a_rMeshes)
	{
		a_rMeshes.resize(m_gameObjects.size());
		
		for (size_t i = 0; i < m_gameObjects.size(); i++)
		{
			a_rMeshes[i] = &m_gameObjects[i].get_mesh();
		}
	}
	GameObject& ObjectEngine::add_game_object(std::string name)
	{
		GameObject newObj{ };
		m_gameObjects.push_back(newObj);
		return m_gameObjects[m_gameObjects.size() - 1];
	}

} // namespace dragonbyte_engine