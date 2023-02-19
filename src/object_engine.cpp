#include "object_engine.h"

#include "mesh.h"

namespace dragonbyte_engine
{

	void ObjectEngine::tick()
	{

	}
	void ObjectEngine::fixed_tick()
	{

	}
	size_t ObjectEngine::get_mesh_count()
	{
		return m_gameObjects.size();
	}
	void ObjectEngine::get_meshes(Mesh** a_ppMeshes)
	{
		size_t meshCount = get_mesh_count();
		if ( a_ppMeshes == nullptr ||
			 sizeof(a_ppMeshes) / sizeof(Mesh) != meshCount)
		{
			throw std::runtime_error("the size of the given mesh array must be same as the mesh count");
			return;
		}
		
		for (size_t i = 0; i < meshCount; i++)
		{
			a_ppMeshes[i] = m_gameObjects[i].get_mesh();
		}
	}
	GameObject_ptr ObjectEngine::add_game_object(std::string name)
	{
		GameObject newObj{ };
		m_gameObjects.push_back(newObj);
		return get_ptr(*(m_gameObjects.end() - 1).base());
	}

} // namespace dragonbyte_engine