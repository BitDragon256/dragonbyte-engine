#include "default_components/time_move.h"
#include "game_object.h"
#include "game_clock.h"

void CTimeMove::tick()
{
	m_pGameObject->m_transform.m_position += m_pGameClock->m_deltaTime;
}