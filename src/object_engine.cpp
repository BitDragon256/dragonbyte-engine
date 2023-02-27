#include "object_engine.h"

#include "mesh.h"

namespace dragonbyte_engine
{

	ObjectEngine::ObjectEngine() :
		m_gameObjects{  }, m_root{  }
	{
		
	}

	void ObjectEngine::tick()
	{
		for (auto& gameObject : m_gameObjects)
		{
			gameObject.tick();
		}
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
	void ObjectEngine::get_transforms(std::vector<Transform*>& a_rTransforms)
	{
		a_rTransforms.resize(m_gameObjects.size());
		for (size_t i = 0; i < m_gameObjects.size(); i++)
		{
			a_rTransforms[i] = &m_gameObjects[i].m_transform;
		}
	}
	GameObject& ObjectEngine::add_game_object(std::string name)
	{
		GameObject newObj{ };
		newObj.m_name = name;
		m_gameObjects.push_back(newObj);
		return m_gameObjects[m_gameObjects.size() - 1];
	}
	GameObject& ObjectEngine::last_game_object()
	{
		return m_gameObjects[m_gameObjects.size() - 1];
	}

} // namespace dragonbyte_engine