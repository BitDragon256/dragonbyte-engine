#include "vulkan/object_info.h"

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
			pWindow = nullptr;
		}

	} // namespace vulkan

} // namespace dragonbyte_engine