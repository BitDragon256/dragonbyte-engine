#pragma once

#include "component.h"
#include "physics_types.h"

namespace dragonbyte_engine
{
	
	class Rigidbody : public Component
	{
	public:

		Rigidbody();

		Velocity m_velocity;
		Acceleration m_acceleration;
		Mass m_mass;

		bool m_isStatic;

		void tick();

		void add_force(Force force);
		void add_force_at_position(Force force, Position relativePosition);

	private:

		Position m_position;
		Position m_lastPosition;
		Position m_globalPosition;

		bool m_firstTick;

		void update_position();
		void update_velocity();
		void law_of_momentum();
		Velocity calc_impact();
		bool intersecting();

		void retrieve_position();
		void apply_position();

	};

} // namespace dragonbyte_engine