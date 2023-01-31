#pragma once

#include <memory>

#include <vulkan/vulkan.h>

namespace dragonbyte_engine
{

	namespace vulkan
	{
		class CommandBuffer;
		class CommandPoolHandler;
		class DebugMessenger;
		class FramebufferHandler;
		class GraphicsPipeline;
		class IndexBuffer;
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
			std::shared_ptr<CommandPoolHandler> pCommandPoolHandler;
			std::shared_ptr<FramebufferHandler> pFramebufferHandler;
			std::shared_ptr<GraphicsPipeline> pGraphicsPipeline;
			std::shared_ptr<IndexBuffer> pIndexBuffer;
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