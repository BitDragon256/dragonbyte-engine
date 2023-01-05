#pragma once

#include <string>
#include <vector>

#include "vulkan/vulkan.h"

#include "engine.h"

#include "vulkan/instance.h"
#include "vulkan/logical_device.h"
#include "vulkan/physical_device.h"
#include "vulkan/window.h"


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

		vulkan::Instance* m_pInstance;
		vulkan::Window* m_pWindow;
		vulkan::PhysicalDevice* m_pPhysicalDevice;
		vulkan::LogicalDevice* m_pLogicalDevice;

		void create_window();
		void create_instance();
		void create_physical_device();
		void create_device();

	};

} // namespace dragonbyte_engine