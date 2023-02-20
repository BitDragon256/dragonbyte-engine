#pragma once

#include <stdint.h>

#include <memory>
#include <vector>

#include "mathematics.h"

namespace dragonbyte_engine
{
    class Component;
    class GameObject;
    class Transform;
    
    typedef Vec3 Position;
    typedef Vec3 Scale;
    typedef Quaternion Rotation;

    typedef struct TransformNode
    {
        TransformNode(Transform* pTransform);

        TransformNode* pParent;
        std::vector<TransformNode*> children;

        Transform* pTransform;

        void add_child(TransformNode* pNode);
        void set_parent(TransformNode* pNode);
    } TransformNode;
    
	typedef class Transform
	{
    public:
        Transform(const GameObject& rThis);

		Position m_position;
		Scale m_scale;
		Rotation m_rotation;

        const GameObject* m_pGameObject;
		
        TransformNode m_node;
		
        void add_child(Transform& rTransform);
        GameObject& add_child(GameObject& rGameObject);
        void set_parent(Transform& rTransform);
        void set_parent(GameObject& rGameObject);
		Position global_position();
		Scale global_scale();
		Rotation global_rotation();
		
	} Transform;
    
    class Rigidbody;
    class Mesh;

    class GameObject
    {
    public:
        
        GameObject();
        GameObject(GameObject& parent);
        GameObject(const GameObject& copy);
        GameObject& operator=(const GameObject& other);

        Transform m_transform;
        std::vector<Component> m_components;
        
        float m_boundingBox;
        
        Rigidbody& get_rigidbody();
        Mesh& get_mesh();
        
        void add_component(const Component& copy_component);
        template<class T> void add_component()
        {
            m_components.push_back((Component) T{});
        }
        template<class T> void add_component(const T& copy_component);
        
        template<class T> T* get_component();
        template<class T> void get_component(T* component);
        
        void tick();
    
    private:
    
        const std::size_t kNoComponent = SIZE_MAX;
        std::size_t m_rigidbodyIndex;
        std::size_t m_meshIndex;
        
        void tick_rb();
        void tick_mesh();
    
    };
    
} // namespace dragonbyte_engine
