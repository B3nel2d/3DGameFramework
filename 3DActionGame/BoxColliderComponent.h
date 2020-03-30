//======================================================================
//
//	BoxColliderComponent
//
//	ボックス(AABB)コライダーのコンポーネントクラス
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
