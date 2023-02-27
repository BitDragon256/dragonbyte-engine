#pragma once

#include <stdint.h>

#include <string>
#include <memory>
#include <vector>

#include "mathematics.h"
#include "component.h"
#include "transform.h"

namespace dragonbyte_engine
{
    
    class Rigidbody;
    class Mesh;

    class GameObject
    {
    public:
        
        GameObject();
        GameObject(Transform& parent);
        GameObject(const GameObject& copy);
        GameObject& operator=(const GameObject& other);

        std::string m_name;

        Transform m_transform;
        std::vector<std::unique_ptr<Component>> m_components;
        
        float m_boundingBox;
        
        Rigidbody& get_rigidbody();
        Mesh& get_mesh();
        void set_mesh(const Mesh& mesh);
        void load_mesh(std::string file);
        
        void add_component(const Component& copy_component);
        template<class T> void add_component()
        {
            check_component_indices(typeid(T), m_components.size());
            m_components.emplace_back(new T {  });
            m_components[m_components.size() - 1]->m_pGameObject = this;
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
        void reset_component_indices();
        void check_component_indices(const std::type_info& krTypeId, size_t index);
        bool has_mesh();
    
    };
    
} // namespace dragonbyte_engine
