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
		virtual ~Component() {};

		GameObject* m_pGameObject;
		
		virtual void tick() {};
		virtual Component* clone() const = 0;

	private:

#define TRANSFORM m_pGameObject->m_transform
#define GAMEOBJECT (*m_pGameObject)
		
	};

} // dragonbyte_engine