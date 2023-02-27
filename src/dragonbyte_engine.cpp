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
		OVERSEER.init_game(a_config);
	}
	void DragonbyteEngine::start_game()
	{
		OVERSEER.run_game();
	}
	Scene& DragonbyteEngine::select_scene(std::string a_name)
	{
		return OBJECT_ENGINE.m_root;
	}

} // namespace dragonbyte_engine