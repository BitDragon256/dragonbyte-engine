#pragma once

#include <cstdlib>

#include <string>
#include <vector>

namespace dragonbyte_engine
{
    class ComputeShader
    {
    private:
        
    public:
        ComputeShader(/* args */);
        ~ComputeShader();
        
        static std::vector<ComputeShader> s_allShaders;
        std::string m_name;
    };
    
} // namespace dragonbyte_engine
