#pragma once

namespace dragonbyte_engine
{
	class GameClock;
	class GameObject;

	class Component
	{
	public:

		Component()
		{}
		Component(GameObject& a_krGameObject) :
			m_pGameObject{ &a_krGameObject }
		{

		}

		GameObject* m_pGameObject;
		
		virtual void tick() {};

	private:

#define TRANSFORM m_pGameObject->m_transform
#define TIME *OVERSEER.m_pGameClock
#define GAMEOBJECT *m_pGameObject
		
	};

} // dragonbyte_engine