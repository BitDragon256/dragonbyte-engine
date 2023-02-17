#pragma once

#include <memory>

namespace dragonbyte_engine
{
	class GameObject;

	typedef std::unique_ptr<GameObject> GameObject_ptr;

} // namespace dragonbyte_engine