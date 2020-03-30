//======================================================================
//
//	BoxColliderComponent
//
//	�{�b�N�X(AABB)�R���C�_�[�̃R���|�[�l���g�N���X
//
//======================================================================

#pragma once

#include "Component.h"
#include "Collision.h"

class BoxColliderComponent : public Component{
	private:
		class TransformComponent* transform;

		AxisAlignedBoundingBox collision;

	public:
		BoxColliderComponent(class Actor* owner, class Level* level, class TransformComponent* transform);
		virtual ~BoxColliderComponent();

		AxisAlignedBoundingBox getWorldCollision();

		const AxisAlignedBoundingBox& getCollision(){return collision;}
		void setCollision(const AxisAlignedBoundingBox& collision){this->collision = collision;}
};
