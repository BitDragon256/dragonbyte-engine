#pragma once

//#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"
//#undef VMA_IMPLEMENTATION

namespace dragonbyte_engine
{
    
    namespace vulkan
    {
        
        class Allocator
        {
            
        public:
                
            Allocator();
            ~Allocator();
            
            void create();
            void destruct();
            
            VmaAllocator m_allocator;
            
        };
        
    } // namespace vulkan
    
    
} // namespace dragonbyte_engine
