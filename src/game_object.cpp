#include "game_object.h"

#include <cassert>
#include <utility>

#include "component.h"
#include "mesh.h"
#include "render_engine.h"
#include "overseer.h"

namespace dragonbyte_engine
{
    
    /* -----------------------------------------------------
    *                       GameObject
    *  -----------------------------------------------------
    */
    GameObject::GameObject() :
        m_transform{ *this }
    {
        reset_component_indices();
    }
    GameObject::GameObject(Transform& a_rParent) :
        m_transform{ *this }
    {
        m_transform.set_parent(a_rParent);

        reset_component_indices();
    }
    GameObject::GameObject(const GameObject& a_krCopy) :
        m_transform{ *this }
    {
        *this = a_krCopy;
    }
    GameObject& GameObject::operator=(const GameObject& a_krOther)
    {
        if (this == &a_krOther)
            return *this;

        m_name = a_krOther.m_name;
        m_transform = a_krOther.m_transform;
        m_boundingBox = a_krOther.m_boundingBox;

        m_rigidbodyIndex = a_krOther.m_rigidbodyIndex;
        m_meshIndex = a_krOther.m_meshIndex;

        // transferring components
        //m_components = std::move(a_krOther.m_components);
        m_components = std::vector<std::unique_ptr<Component>>();
        for (size_t i = 0; i < a_krOther.m_components.size(); i++)
        {
            m_components.emplace_back(a_krOther.m_components[i]->clone());
            m_components[i]->m_pGameObject = a_krOther.m_components[i]->m_pGameObject;
        }

        return *this;
    }

    void GameObject::tick()
    {
        for (std::size_t i = 0; i < m_components.size(); i++)
        {
            m_components[i]->tick();
        }
    }
    Mesh& GameObject::get_mesh()
    {
        assert(has_mesh() && "GameObject does not posess a mesh");
        assert(m_components.size() > m_meshIndex && "Mesh Component does not exist or is at wrong position");
        return *dynamic_cast<Mesh*>(m_components[m_meshIndex].get());
    }
    void GameObject::set_mesh(const Mesh& a_mesh)
    {
        if (!has_mesh())
            add_component<Mesh>();

        get_mesh() = a_mesh;
        get_mesh().bind_to_handler();
    }
    void GameObject::load_mesh(std::string a_file)
    {
        const Mesh mesh = Mesh::load_mesh(a_file);
        set_mesh(mesh);
    }
    void GameObject::reset_component_indices()
    {
        m_rigidbodyIndex = kNoComponent;
        m_meshIndex = kNoComponent;
    }
    void GameObject::check_component_indices(const std::type_info& a_krTypeId, size_t a_index)
    {
        if (a_krTypeId == typeid(Mesh))
        {
            m_meshIndex = a_index;
        }
    }
    bool GameObject::has_mesh()
    {
        return m_meshIndex != kNoComponent;
    }
    
    
} // namespace dragonbyte_engine
