#include "ptr_types.h"
#include "game_object.h"
#include "component.h"
#include "scene.h"

namespace dragonbyte_engine
{
    
    GameObject_ptr get_ptr(GameObject& a_rGameObject)
	{
		return std::make_unique<GameObject>(a_rGameObject);
	}
	Scene_ptr get_ptr(Scene& a_rScene)
	{
        return std::make_unique<Scene>(a_rScene);
	}
    
} // namespace dragonbyte_engine
