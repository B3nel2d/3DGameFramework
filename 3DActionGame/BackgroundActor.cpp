#include "BackgroundActor.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "Game.h"

/**********************************************************************
	�R���X�g���N�^�[
**********************************************************************/
BackgroundActor::BackgroundActor(Level* level) : Actor(level){
	transform = new TransformComponent(this);
	sprite = new SpriteComponent(this, level);
}

/**********************************************************************
	�f�R���X�g���N�^�[
**********************************************************************/
BackgroundActor::~BackgroundActor(){

}

/**********************************************************************
	update

	���t���[���ł̏������s��
**********************************************************************/
void BackgroundActor::update(){
	Actor::update();
}
