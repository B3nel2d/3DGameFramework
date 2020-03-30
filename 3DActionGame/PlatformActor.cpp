#include "PlatformActor.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "BoxColliderComponent.h"

/**********************************************************************
	�R���X�g���N�^�[
**********************************************************************/
PlatformActor::PlatformActor(Level* level) : Actor(level){
	transform = new TransformComponent(this);

	mesh = new MeshComponent(this, level);
	mesh->initialize("assets\\models\\cube.x");

	boxCollider = new BoxColliderComponent(this, level, transform);
	boxCollider->setCollision(AxisAlignedBoundingBox(Vector3D(-0.5f, -0.5f, -0.5f), Vector3D(0.5f, 0.5f, 0.5f)));
}

/**********************************************************************
	�f�R���X�g���N�^�[
**********************************************************************/
PlatformActor::~PlatformActor(){

}
