#include "BoxColliderComponent.h"
#include "Level.h"
#include "Actor.h"
#include "TransformComponent.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
BoxColliderComponent::BoxColliderComponent(Actor* owner, Level* level, TransformComponent* transform) : Component(owner){
	level->getPhysics()->addCollider(this);
	this->transform = transform;
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
BoxColliderComponent::~BoxColliderComponent(){
	owner->getLevel()->getPhysics()->removeCollider(this);
}

/**********************************************************************
	getWorldCollision

	ワールド座標系でのコライダーを取得する
**********************************************************************/
AxisAlignedBoundingBox BoxColliderComponent::getWorldCollision(){
	return AxisAlignedBoundingBox(collision.minimumPoint.transform(Matrix4x4::getWorldMatrix(transform)), collision.maximumPoint.transform(Matrix4x4::getWorldMatrix(transform)));
}
