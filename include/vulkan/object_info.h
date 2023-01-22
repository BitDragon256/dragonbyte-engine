#pragma once

#include <memory>

#include <vulkan/vulkan.h>

//#include "debug_messenger.h"
//#include "framebuffer.h"
//#include "graphics_pipeline.h"
//#include "instance.h"
//#include "logical_device.h"
//#include "physical_device.h"
//#include "render_pass.h"
//#include "surface.h"
//#include "swapchain.h"
//#include "window.h"

namespace dragonbyte_engine
{

	namespace vulkan
	{
		class CommandBuffer;
		class CommandPool;
		class DebugMessenger;
		class FramebufferHandler;
		class GraphicsPipeline;
		class Instance;
		class LogicalDevice;
		class PhysicalDevice;
		class RenderPass;
		class Surface;
		class SwapChain;
		class SyncHandler;
		class VertexBuffer;
		class Window;

		struct ObjectInfo
		{
			ObjectInfo();
			~ObjectInfo();

			std::shared_ptr<class DebugMessenger> pDebugMessenger;
			std::shared_ptr<CommandBuffer> pCommandBuffer;
			std::shared_ptr<CommandPool> pCommandPool;
			std::shared_ptr<FramebufferHandler> pFramebufferHandler;
			std::shared_ptr<GraphicsPipeline> pGraphicsPipeline;
			std::shared_ptr<Instance> pInstance;
			std::shared_ptr<LogicalDevice> pLogicalDevice;
			std::shared_ptr<PhysicalDevice> pPhysicalDevice;
			std::shared_ptr<RenderPass> pRenderPass;
			std::shared_ptr<Surface> pSurface;
			std::shared_ptr<SwapChain> pSwapChain;
			std::shared_ptr<SyncHandler> pSyncHandler;
			std::shared_ptr<VertexBuffer> pVertexBuffer;
			std::shared_ptr<Window> pWindow;

			void reset();
			
			static ObjectInfo s_ObjectInfo;
		};
		
		#define oi ObjectInfo::s_ObjectInfo
		
	} // namespace vulkan

} // namespace dragonbyte_engine