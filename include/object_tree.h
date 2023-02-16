#pragma once

#include <vector>

namespace dragonbyte_engine
{
    
    class GameObject;
    
    class GameObjectTree
    {
    public:
        GameObjectTree();
        ~GameObjectTree();
        
        struct Node
        {
            std::vector<GameObject> objects;
            
        };
    };
    
} // namespace dragonbyte_engine
