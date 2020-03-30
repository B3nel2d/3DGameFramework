#include "MeshComponent.h"
#include "TransformComponent.h"
#include "Actor.h"
#include "Game.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
MeshComponent::MeshComponent(class Actor* owner, class Level* level) : Component(owner){
	transform = owner->getComponent<TransformComponent>();
	level->getRenderer()->addMesh(this);
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
MeshComponent::~MeshComponent(){
	owner->getLevel()->getRenderer()->removeMesh(this);
}

/**********************************************************************
	initialize

	初期化を行う
**********************************************************************/
void MeshComponent::initialize(const char* fileName){
	Game::getInstance()->getGraphics()->loadMesh(fileName);
	mesh = Game::getInstance()->getGraphics()->getMesh(fileName);
}

/**********************************************************************
	draw

	描画を行う
**********************************************************************/
void MeshComponent::draw(){
	Game::getInstance()->getGraphics()->drawMesh(mesh, transform);
}
