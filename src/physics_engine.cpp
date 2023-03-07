#include "physics_engine.h"

#include "default_components/rigidbody.h"
#include "game_object.h"

#include "mathematics.h"

namespace dragonbyte_engine
{

	void PhysicsEngine::create()
	{
	
	}
	void PhysicsEngine::tick()
	{
		for (auto rb : m_allRigidbodies)
		{
			rb->tick();
		}
	}
	
	void PhysicsEngine::add_rigidbody(Rigidbody& a_rRigidbody)
	{
		m_allRigidbodies.push_back(&a_rRigidbody);
	}
	void PhysicsEngine::detect_collisions()
	{
		m_intersectingVolumeRigidbodies.reserve(m_allRigidbodies.size());
	
		broad_phase();
		narrow_phase();
	}
	void PhysicsEngine::broad_phase()
	{
		GameObject* a, *b;
		for (auto rb : m_allRigidbodies)
		{
			for (auto in : m_allRigidbodies)
			{
				a = rb->m_pGameObject;
				b = in->m_pGameObject;
				if (Vec3::distance(a->m_transform.m_position, b->m_transform.m_position) < a->m_boundingSphere + b->m_boundingSphere)
				{
					m_intersectingVolumeRigidbodies.push_back(rb);
				}
			}
		}
	}
	void PhysicsEngine::narrow_phase()
	{
	
	}

} // namespace dragonbyte_engine