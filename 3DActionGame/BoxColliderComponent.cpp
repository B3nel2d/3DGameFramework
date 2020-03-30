#include "BoxColliderComponent.h"
#include "Level.h"
#include "Actor.h"
#include "TransformComponent.h"

/**********************************************************************
	�R���X�g���N�^�[
**********************************************************************/
BoxColliderComponent::BoxColliderComponent(Actor* owner, Level* level, TransformComponent* transform) : Component(owner){
	level->getPhysics()->addCollider(this);
	this->transform = transform;
}

/**********************************************************************
	�f�R���X�g���N�^�[
**********************************************************************/
BoxColliderComponent::~BoxColliderComponent(){
	owner->getLevel()->getPhysics()->removeCollider(this);
}

/**********************************************************************
	getWorldCollision

	���[���h���W�n�ł̃R���C�_�[���擾����
**********************************************************************/
AxisAlignedBoundingBox BoxColliderComponent::getWorldCollision(){
	return AxisAlignedBoundingBox(collision.minimumPoint.transform(Matrix4x4::getWorldMatrix(transform)), collision.maximumPoint.transform(Matrix4x4::getWorldMatrix(transform)));
}
