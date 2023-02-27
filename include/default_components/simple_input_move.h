#pragma once

#include "component.h"

class CSimpleInputMove : public dragonbyte_engine::Component
{
public:
	float speed = 3.f;
	void tick() override;
};