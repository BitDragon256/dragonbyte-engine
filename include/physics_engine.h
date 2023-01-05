#pragma once

#include "engine.h"
#include "component.h"

namespace dragonbyte_engine
{
	class PhysicsEngine : public Engine
	{
	public:

		void tick() override;

	private:



	};

	// 
	class Rigidbody : Component
	{

	};

} // namespace dragonbyte_engine