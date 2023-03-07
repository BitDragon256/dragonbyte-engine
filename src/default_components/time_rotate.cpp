#include "default_components/time_rotate.h"

#include <math.h>

#include "transform.h"
#include "game_object.h"
#include "game_clock.h"
#include "overseer.h"

using namespace dragonbyte_engine;

void CTimeRotate::tick()
{
    TRANSFORM.m_rotation.z += GAME_CLOCK.m_deltaTime * 70;
    TRANSFORM.m_rotation.y += GAME_CLOCK.m_deltaTime * 50;
    
    TRANSFORM.m_position.x = sin(time - TRANSFORM.m_position.y * TRANSFORM.m_position.z / 100.0);
    time += GAME_CLOCK.m_deltaTime;
}