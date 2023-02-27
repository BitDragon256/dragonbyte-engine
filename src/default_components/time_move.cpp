#include "default_components/time_move.h"
#include "game_object.h"
#include "game_clock.h"

#include <iostream>

void CTimeMove::tick()
{
	m_pGameObject->m_transform.m_position.x += m_pGameClock->m_deltaTime;
}