#pragma once

#include <string>
#include <vector>

#include <vulkan/vulkan.h>

#include "engine.h"

#include "vulkan/object_info.h"

namespace dragonbyte_engine
{

	typedef enum { Rasterization, RayTracing } RenderType;

	struct RenderEngineConfig
	{
		bool renderModels;
		bool renderParticles;
		bool renderGui;

		uint32_t windowHeight;
		uint32_t windowWidth;

		const char* applicationName; 
		const char* engineName;

		RenderType renderType;
	};

	// namespace vulkan { struct ObjectInfo; }

	class RenderEngine : Engine
	{
	public:

		RenderEngine(const RenderEngineConfig& a_kConfig);
		~RenderEngine();

		RenderEngineConfig m_config;

		void tick() override;

		void render_particles();
		void render_models();
		void render_gui();

		void animation_tick();
		
		bool should_close_window();

	private:

		vulkan::ObjectInfo m_vkObjectInfo;

		void setup_vulkan();

		void create_debug_messenger(); 
		void create_device();
		void create_graphics_pipeline();
		void create_instance();
		void get_physical_device();
		void create_render_pass();
		void create_surface();
		void create_swap_chain();
		void create_window();

	};

} // n amespace dragonbyte_engine