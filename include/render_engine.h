#pragma once

#include "vulkan/vulkan.h"

#include "engines.h"

#include "graphics/pipeline.h"
#include "graphics/swapchain.h"
#include "graphics/window.h"

namespace dragonbyte_engine
{

	struct RenderEngineConfig
	{
		bool renderModels;
		bool renderParticles;
		bool renderGui;
	};

	class RenderEngine : Engine
	{
	public:
		RenderEngine(const RenderEngineConfig& config);

		RenderEngineConfig m_config;

		void initialize() override;
		void tick() override;
		void destruct() override;

		void render_particles();
		void render_models();
		void render_gui();

		void animation_tick();

		bool should_close_window();

	private:

		graphics::Window* m_window;
		graphics::Pipeline m_graphicsPipeline;
		graphics::Swapchain m_swapchain;

		VkInstance m_vkInstance;
		VkPhysicalDevice m_physicalDevice;
		VkDevice m_device;

		VkSurfaceKHR m_surface;

		void create_window();
		void create_vk_instance();
		void get_physical_device();
		void create_device();
		void get_surface();
		void create_swapchain();

	};

} // namespace dragonbyte_engine