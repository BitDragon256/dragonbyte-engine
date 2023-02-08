#pragma once

#include "game_object.h"

namespace dragonbyte_engine
{

	class Component
	{
	public:
		
		GameObject& m_rGameObject;
		
		virtual void tick() = 0;
		
	};

} // dragonbyte_engine