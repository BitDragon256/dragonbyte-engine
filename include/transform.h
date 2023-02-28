#pragma once

#include <vector>
#include "mathematics.h"

namespace dragonbyte_engine
{
    class GameObject;
    class Transform;
    
    typedef Vec3 Position;
    typedef Vec3 Scale;
    typedef Vec3 Rotation;

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

        Position up();
        Position forward();
        Position right();

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
    
} // namespace dragonbyte_engine
