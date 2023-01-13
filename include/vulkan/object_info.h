#pragma once

#include <memory>

#include <vulkan/vulkan.h>

#include "debug_messenger.h"
#include "framebuffer.h"
#include "graphics_pipeline.h"
#include "instance.h"
#include "logical_device.h"
#include "physical_device.h"
#include "render_pass.h"
#include "surface.h"
#include "swapchain.h"
#include "window.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{

		struct ObjectInfo
		{
			ObjectInfo();
			~ObjectInfo();

			std::unique_ptr<DebugMessenger> pDebugMessenger;
			std::unique_ptr<FramebufferHandler> pFramebufferHandler;
			std::unique_ptr<GraphicsPipeline> pGraphicsPipeline;
			std::unique_ptr<Instance> pInstance;
			std::unique_ptr<LogicalDevice> pLogicalDevice;
			std::unique_ptr<PhysicalDevice> pPhysicalDevice;
			std::unique_ptr<RenderPass> pRenderPass;
			std::unique_ptr<Surface> pSurface;
			std::unique_ptr<SwapChain> pSwapChain;
			std::unique_ptr<Window> pWindow;

			void reset();
		};

	} // namespace vulkan

} // namespace dragonbyte_engine