#pragma once

#include <string>

#include "overseer.h"
// #include "game_object.h"
#include "scene.h"
#include "mathematics.h"

namespace dragonbyte_engine
{
	struct PhysicsConfig
	{
		float gravity;
	};
	struct WindowConfig
	{
		bool fullscreen;
		uint32_t width;
		uint32_t height;
	};
	struct EngineConfig
	{
		EngineConfig();

		float targetFps;
		bool useDefaultCamera;

		WindowConfig window;
		PhysicsConfig physics;
	};
	
	//class Overseer;
	//class Scene;

	class DragonbyteEngine
	{
	public:

		DragonbyteEngine();

		void create(EngineConfig config);
		void start_game();

		void add_scene(std::string name);
		Scene* select_scene(std::string name);

		Overseer m_overseer;
	};
} // namespace dragonbyte_engine