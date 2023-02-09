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
	class Mesh;

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

		void set_static_meshes(std::vector<Mesh&> meshes);

	private:
	
		void setup_vulkan();

		void create_window();
		
		void create_instance();
		void create_debug_messenger(); 
		void create_surface();
		void get_physical_device();
		void create_device();
		void create_swap_chain();
		void create_render_pass();
		void create_graphics_pipeline();
		void create_framebuffer();
		void create_command_pool_handler();
		void create_command_buffer();
		void create_sync_objects();
		void create_allocator();
		void create_vertex_buffer();
		void create_index_buffer();
		void create_descriptor_set_handler();
		void create_uniform_buffer_handler();
		void create_mvp_buffer_handler();
		void create_descriptor_pool();
		void create_descriptor_set_layout();
		void create_depth_handler();

		void draw_frame();
		void update_uniform_buffer_handler(uint32_t currentImage);
		void update_storage_buffer_handler(uint32_t currentImage);
		void record_command_buffer(uint32_t imageIndex);
		void submit_command_buffer();
		void present(uint32_t imageIndex);

	};

} // n amespace dragonbyte_engine