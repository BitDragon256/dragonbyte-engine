#include "default_components/time_move.h"

#include <iostream>

#include "game_object.h"
#include "game_clock.h"
#include "overseer.h"
using namespace dragonbyte_engine;

void CTimeMove::tick()
{
	TRANSFORM.m_position.x += GAME_CLOCK.m_deltaTime;
}