#pragma once

#include <stdint.h>

#include <vector>

#include "mathematics.h"

namespace dragonbyte_engine
{
    class Component;
    
    typedef Vec3 Position;
    typedef Vec3 Scale;
    typedef Quaternion Rotation;
    
	typedef struct Transform
	{
    public:

		Position m_position;
		Scale m_scale;
		Rotation m_rotation;
		
		std::vector<Transform*> m_children;
		Transform* m_parent;
		
		Position global_position();
		Scale global_scale();
		Rotation global_rotation();
		
	} Transform;
    
    class Rigidbody;
    class Mesh;

    class GameObject
    {
    public:
        
        Transform m_transform;
        std::vector<Component> m_components;
        
        float m_boundingBox;
        
        Rigidbody& get_rigidbody();
        Mesh& get_mesh();
        
        void add_component(const Component& copy_component);
        template<class T> void add_component();
        template<class T> void add_component(const T& copy_component);
        
        template<class T> T& get_component();
        template<class T> void get_component(T& component);
        
        void tick();
    
    private:
    
        const std::size_t kNoComponent = SIZE_MAX;
        std::size_t m_rigidbodyIndex;
        std::size_t m_meshIndex;
        
        void tick_rb();
        void tick_mesh();
    
    };
    
} // namespace dragonbyte_engine
