#include "vulkan/object_info.h"

#include "vulkan/debug_messenger.h"
#include "vulkan/framebuffer.h"
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

	namespace vulkan
	{

		ObjectInfo::ObjectInfo()
		{
			reset();
		}
		ObjectInfo::~ObjectInfo()
		{
			
		}

		void ObjectInfo::reset()
		{
			pDebugMessenger = nullptr;
			pFramebufferHandler = nullptr;
			pGraphicsPipeline = nullptr;
			pInstance = nullptr;
			pLogicalDevice = nullptr;
			pPhysicalDevice = nullptr;
			pRenderPass = nullptr;
			pSurface = nullptr;
			pSwapChain = nullptr;
			pSyncHandler = nullptr;
			pWindow = nullptr;
		}
		
		ObjectInfo ObjectInfo::s_ObjectInfo = {};

	} // namespace vulkan

} // namespace dragonbyte_engine