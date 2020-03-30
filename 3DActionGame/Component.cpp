#include "Component.h"
#include "Actor.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
Component::Component(Actor* owner, int updateOrder){
	this->state = active;

	this->owner = owner;
	this->updateOrder = updateOrder;

	owner->addComponent(this);
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
Component::~Component(){
	owner->removeComponent(this);
}

/**********************************************************************
	update

	毎フレームでの処理を行う
**********************************************************************/
void Component::update(){
	if(state != active){
		return;
	}
}
