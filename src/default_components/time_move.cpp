#include "default_components/time_move.h"

void CTimeMove::tick()
{
	m_pGameObject->m_transform.m_position += m_pGameClock->m_deltaTime;
}