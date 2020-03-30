#include "PlayerActor.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"
#include "MeshComponent.h"
#include "SpriteComponent.h"
#include "Game.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
PlayerActor::PlayerActor(Level* level) : Actor(level){
	transform = new TransformComponent(this);

	mesh = new MeshComponent(this, level);
	mesh->initialize("assets\\models\\cube.x");

	boxCollider = new BoxColliderComponent(this, level, transform);
	boxCollider->setCollision(AxisAlignedBoundingBox(Vector3D(-0.5f, -0.5f, -0.5f), Vector3D(0.5f, 0.5f, 0.5f)));

	movementSpeed = 5.0f;
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
PlayerActor::~PlayerActor(){

}

/**********************************************************************
	update

	毎フレームでの処理を行う
**********************************************************************/
void PlayerActor::update(){
	Actor::update();

    if(Game::getInstance()->getInput()->isKeyDown(VK_RIGHT)){
		transform->translate(Vector3D(movementSpeed * Game::getInstance()->getFrameDeltaTime(), 0.0f, 0.0f));
    }
    if(Game::getInstance()->getInput()->isKeyDown(VK_LEFT)){
		transform->translate(Vector3D(-movementSpeed * Game::getInstance()->getFrameDeltaTime(), 0.0f, 0.0f));
    }
    if(Game::getInstance()->getInput()->isKeyDown(VK_UP)){
		transform->translate(Vector3D(0.0f, movementSpeed * Game::getInstance()->getFrameDeltaTime(), 0.0f));
    }
    if(Game::getInstance()->getInput()->isKeyDown(VK_DOWN)){
		transform->translate(Vector3D(0.0f, -movementSpeed * Game::getInstance()->getFrameDeltaTime(), 0.0f));
    }
}
