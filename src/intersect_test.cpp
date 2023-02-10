/*

#include <vector>

#include "game_object.h"
#include "mesh.h"
#include "mathematics.h"

namespace dragonbyte_engine
{
    
    bool intersect(GameObject& a, GameObject& b)
    {
        return false;
    }
    bool intersecting(GameObject a_this, std::vector<GameObject> a_objects)
    {
        Mesh mesh = a_this.get_mesh();
        for (size_t i = 0; i < a_objects.size(); i++)
        {
            float minDist = a_this.m_boundingBox + a_objects[i].m_boundingBox;
            if (Vec3::distance(a_this.m_transform.m_position, a_objects[i].m_transform.m_position) < minDist)
            {
                intersect(a_this, a_objects[i]);
            }
        }
        
        return false;
    }
    
} // namespace dragonbyte_engine

*/