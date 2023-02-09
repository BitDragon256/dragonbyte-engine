#pragma once

#include "game_object.h"
#include "game_clock.h"

namespace dragonbyte_engine
{
	class GameClock;

	class Component
	{
	public:

		Component(GameObject& a_krGameObject, GameClock& a_krGameClock) :
			m_rGameObject{ a_krGameObject }, m_rGameClock{ a_krGameClock }
		{

		}

		GameObject& m_rGameObject;
		GameClock& m_rGameClock;
		
		virtual void tick() = 0;
		
	};

} // dragonbyte_engine