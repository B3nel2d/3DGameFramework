#include "FPSTextActor.h"
#include "Level.h"
#include "UITransformComponent.h"
#include "TextComponent.h"
#include "Game.h"

/**********************************************************************
	�R���X�g���N�^�[
**********************************************************************/
FPSTextActor::FPSTextActor(Level* level) : Actor(level){
	uiTransform = new UITransformComponent(this);
	text = new TextComponent(this, level);
}

/**********************************************************************
	�f�R���X�g���N�^�[
**********************************************************************/
FPSTextActor::~FPSTextActor(){

}

/**********************************************************************
	update

	���t���[���ł̏������s��
**********************************************************************/
void FPSTextActor::update(){
	text->setString(std::to_string((int)(Game::getInstance()->getFramePerSecond())));
}
