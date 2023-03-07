#pragma once

#include <vector>

namespace dragonbyte_engine
{
	class Rigidbody;

	class PhysicsEngine
	{
	public:

		float gravity;

		void create();
		void tick();
		
		void add_rigidbody(Rigidbody& rRigidbody);

	private:

		std::vector<Rigidbody*> m_allRigidbodies;
		
		std::vector<Rigidbody*> m_intersectingVolumeRigidbodies;
		void detect_collisions();
		void broad_phase();
		void narrow_phase();

	};

} // namespace dragonbyte_engine