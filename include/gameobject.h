#pragma once

#include <vector>

#include "component.h"
#include "mathematics.h"

namespace dragonbyte_engine
{

	typedef struct
	{
		Vec3 position;
		Vec3 scale;
		Quaternion rotation;
	} Transform;

	class GameObject
	{
	public:

		Transform m_transform;

		std::vector<Component> m_components;

	private:
	};

} // dragonbyte_engine