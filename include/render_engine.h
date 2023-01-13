#pragma once

#include <string>
#include <vector>

#include "vulkan/vulkan.h"

#include "engine.h"

#include "vulkan/debug_messenger.h"
#include "vulkan/graphics_pipeline.h"
#include "vulkan/instance.h"
#include "vulkan/logical_device.h"
#include "vulkan/physical_device.h"
#include "vulkan/render_pass.h"
#include "vulkan/surface.h"
#include "vulkan/swapchain.h"
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

		vulkan::DebugMessenger* m_pDebugMessenger;
		vulkan::GraphicsPipeline* m_pGraphicsPipeline;
		vulkan::Instance* m_pInstance;
		vulkan::LogicalDevice* m_pLogicalDevice;
		vulkan::PhysicalDevice* m_pPhysicalDevice;
		vulkan::RenderPass* m_pRenderPass;
		vulkan::Surface* m_pSurface;
		vulkan::SwapChain* m_pSwapChain;
		vulkan::Window* m_pWindow;

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