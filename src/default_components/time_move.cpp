#include "default_components/time_move.h"

#include <iostream>

#include "game_object.h"
#include "game_clock.h"
using namespace dragonbyte_engine;

void CTimeMove::tick()
{
	TRANSFORM.m_position.x += TIME.m_deltaTime;
}