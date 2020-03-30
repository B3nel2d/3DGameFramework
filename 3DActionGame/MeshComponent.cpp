#include "MeshComponent.h"
#include "TransformComponent.h"
#include "Actor.h"
#include "Game.h"

/**********************************************************************
	�R���X�g���N�^�[
**********************************************************************/
MeshComponent::MeshComponent(class Actor* owner, class Level* level) : Component(owner){
	transform = owner->getComponent<TransformComponent>();
	level->getRenderer()->addMesh(this);
}

/**********************************************************************
	�f�R���X�g���N�^�[
**********************************************************************/
MeshComponent::~MeshComponent(){
	owner->getLevel()->getRenderer()->removeMesh(this);
}

/**********************************************************************
	initialize

	���������s��
**********************************************************************/
void MeshComponent::initialize(const char* fileName){
	Game::getInstance()->getGraphics()->loadMesh(fileName);
	mesh = Game::getInstance()->getGraphics()->getMesh(fileName);
}

/**********************************************************************
	draw

	�`����s��
**********************************************************************/
void MeshComponent::draw(){
	Game::getInstance()->getGraphics()->drawMesh(mesh, transform);
}
