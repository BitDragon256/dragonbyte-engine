#include <vector>

#include "game_object.h"
#include "mesh.h"
#include "mathematics.h"

namespace dragonbyte_engine
{
    
    
    bool intersecting(GameObject a_this, std::vector<GameObject> a_objects)
    {
        Mesh mesh = a_this.get_mesh();
        for (size_t i = 0; i < a_objects.size(); i++)
        {
            float minDist = a_this.m_boundingBox + a_objects[i].m_boundingBox;
            if (Vec3::distance(a_this.m_transform.position, a_objects[i].m_transform.position) < minDist)
            {
                intersect(a_this, a_objects[i]);
            }
        }
    }
    bool intersect(GameObject& a, GameObject& b)
    {
        
    }
    
} // namespace dragonbyte_engine
