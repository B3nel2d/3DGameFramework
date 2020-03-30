#include "CameraActor.h"
#include "Level.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
CameraActor::CameraActor(Level* level) : Actor(level){
	transform = new TransformComponent(this);
	camera = new CameraComponent(this, transform);

	camera->setLookPosition(Vector3D::zero);
	camera->setUpVector(Vector3D::up);
	camera->setFieldOfView(Math::toRadian(30.0f));
	camera->setNearClippingPlaneDistance(10.0f);
	camera->setFarClippingPlaneDistance(1000.0f);
	camera->setBackgroundColor(Color::blue);
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
CameraActor::~CameraActor(){

}
