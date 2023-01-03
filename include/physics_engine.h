#pragma once

#include "engines.h"
#include "component.h"

namespace dragonbyte_engine
{
	class PhysicsEngine : public Engine
	{
	public:

		void tick() override;
		void initialize() override;
		void destruct() override;

	private:



	};

	// 
	class Rigidbody : Component
	{

	};

} // namespace dragonbyte_engine