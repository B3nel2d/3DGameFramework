#include "FPSTextActor.h"
#include "Level.h"
#include "UITransformComponent.h"
#include "TextComponent.h"
#include "Game.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
FPSTextActor::FPSTextActor(Level* level) : Actor(level){
	uiTransform = new UITransformComponent(this);
	text = new TextComponent(this, level);
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
FPSTextActor::~FPSTextActor(){

}

/**********************************************************************
	update

	毎フレームでの処理を行う
**********************************************************************/
void FPSTextActor::update(){
	text->setString(std::to_string((int)(Game::getInstance()->getFramePerSecond())));
}
