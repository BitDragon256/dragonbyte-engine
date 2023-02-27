#include "default_components/simple_input_move.h"

#include "overseer.h"
#include "game_clock.h"
#include "game_object.h"
#include "input_engine.h"

using namespace dragonbyte_engine;

void CSimpleInputMove::tick()
{
	if (INPUT.get_key('W'))
	{
		TRANSFORM.m_position.x += speed * GAME_CLOCK.m_deltaTime;
	}
	if (INPUT.get_key('S'))
	{
		TRANSFORM.m_position.x -= speed * GAME_CLOCK.m_deltaTime;
	}
	if (INPUT.get_key('A'))
	{
		TRANSFORM.m_position.y += speed * GAME_CLOCK.m_deltaTime;
	}
	if (INPUT.get_key('D'))
	{
		TRANSFORM.m_position.y -= speed * GAME_CLOCK.m_deltaTime;
	}
}