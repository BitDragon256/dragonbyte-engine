#pragma once

#include "game_object.h"
#include "game_clock.h"

namespace dragonbyte_engine
{
	class GameClock;

	class Component
	{
	public:

		Component()
		{}
		Component(GameObject& a_krGameObject, GameClock& a_krGameClock) :
			m_pGameObject{ &a_krGameObject }, m_pGameClock{ &a_krGameClock }
		{

		}

		GameObject* m_pGameObject;
		GameClock* m_pGameClock;
		
		virtual void tick() {};
		
	};

} // dragonbyte_engine