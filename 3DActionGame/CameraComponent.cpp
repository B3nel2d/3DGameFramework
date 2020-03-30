#include "CameraComponent.h"
#include "Actor.h"
#include "TransformComponent.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
CameraComponent::CameraComponent(Actor* owner, TransformComponent* transform) : Component(owner){
	this->transform = transform;

	lookPosition = Vector3D::zero;
	upVector = Vector3D::up;

	fieldOfView = Math::toRadian(30.0f);
	nearClippingPlaneDistance = 10.0f;
	farClippingPlaneDistance = 1000.0f;

	backgroundColor = Color::black;
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
CameraComponent::~CameraComponent(){

}
