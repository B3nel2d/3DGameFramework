#include "Component.h"
#include "Actor.h"

/**********************************************************************
	�R���X�g���N�^�[
**********************************************************************/
Component::Component(Actor* owner, int updateOrder){
	this->state = active;

	this->owner = owner;
	this->updateOrder = updateOrder;

	owner->addComponent(this);
}

/**********************************************************************
	�f�R���X�g���N�^�[
**********************************************************************/
Component::~Component(){
	owner->removeComponent(this);
}

/**********************************************************************
	update

	���t���[���ł̏������s��
**********************************************************************/
void Component::update(){
	if(state != active){
		return;
	}
}
