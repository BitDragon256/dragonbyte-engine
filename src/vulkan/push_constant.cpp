#include "vulkan/push_constant.h"

std::vector<VkPushConstantRange> dragonbyte_engine::vulkan::AllPushConstantRanges::s_ranges = {};
size_t dragonbyte_engine::vulkan::AllPushConstantRanges::s_size = 0;