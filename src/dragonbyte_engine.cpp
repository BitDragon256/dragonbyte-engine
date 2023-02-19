#include "dragonbyte_engine.h"
#include "object_engine.h"

namespace dragonbyte_engine
{

	EngineConfig::EngineConfig()
	{
	
	}

	DragonbyteEngine::DragonbyteEngine()
	{}

	void DragonbyteEngine::create(EngineConfig a_config)
	{
		m_overseer.init_game(a_config);
	}
	void DragonbyteEngine::start_game()
	{
		m_overseer.run_game();
	}
	Scene_ptr DragonbyteEngine::select_scene(std::string a_name)
	{
		return get_ptr(m_overseer.m_pObjectEngine->m_root);
	}

} // namespace dragonbyte_engine