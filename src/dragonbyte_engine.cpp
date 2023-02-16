#include "dragonbyte_engine.h"

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

} // namespace dragonbyte_engine