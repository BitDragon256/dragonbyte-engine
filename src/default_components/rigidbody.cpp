#include "default_components/rigidbody.h"
#include "game_clock.h"

namespace dragonbyte_engine
{

	Rigidbody::Rigidbody(GameObject& a_krGameObject, GameClock& a_krGameClock) :
		m_firstTick{ true }, Component(a_krGameObject, a_krGameClock)
	{

	}

	void Rigidbody::tick()
	{
		retrieve_position();

		update_velocity();
		update_position();

		apply_position();

		if (m_firstTick)
			m_firstTick = false;
	}
	void Rigidbody::add_force(Force a_force)
	{
		m_acceleration += a_force / m_mass;
	}
	void Rigidbody::add_force_at_position(Force a_force, Position a_position)
	{

	}

	void Rigidbody::update_position()
	{
		law_of_momentum();
	}
	void Rigidbody::update_velocity()
	{
		if (m_firstTick)
			m_lastPosition = m_position;

		m_velocity = m_lastPosition - m_position;

		m_velocity += m_acceleration * m_rGameClock.m_deltaTime;
	}
	void Rigidbody::law_of_momentum()
	{
		m_position += m_velocity * m_rGameClock.m_deltaTime;
		m_globalPosition += m_velocity * m_rGameClock.m_deltaTime;
	}
	Velocity Rigidbody::calc_impact()
	{
		return {};
	}
	bool Rigidbody::intersecting()
	{
		return false;
	}

	void Rigidbody::retrieve_position()
	{
		m_position = m_rGameObject.m_transform.m_position;
		m_globalPosition = m_rGameObject.m_transform.global_position();
	}
	void Rigidbody::apply_position()
	{
		m_rGameObject.m_transform.m_position = m_position;

		m_lastPosition = m_position;
	}

} // namespace dragonbyte_engine