#include "BackgroundActor.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "Game.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
BackgroundActor::BackgroundActor(Level* level) : Actor(level){
	transform = new TransformComponent(this);
	sprite = new SpriteComponent(this, level);
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
BackgroundActor::~BackgroundActor(){

}

/**********************************************************************
	update

	毎フレームでの処理を行う
**********************************************************************/
void BackgroundActor::update(){
	Actor::update();
}
