#include "Actor.h"
#include <algorithm>
#include "Game.h"
#include "Level.h"
#include "Component.h"
#include "Settings.h"

/**********************************************************************
	�R���X�g���N�^�[
**********************************************************************/
Actor::Actor(class Level* level){
	state = active;
	tag = none;

	this->level = level;
	level->addActor(this);
}

/**********************************************************************
	�f�R���X�g���N�^�[
**********************************************************************/
Actor::~Actor(){
	level->removeActor(this);

	while(!components.empty()){
		delete components.back();
	}
}

/**********************************************************************
	update

	���t���[���ł̏������s��
**********************************************************************/
void Actor::update(){
	if(state != active){
		return;
	}

	for(Component* component : components){
		component->update();
	}
}

/**********************************************************************
	addComponent

	�w�肵���R���|�[�l���g��ǉ�����
**********************************************************************/
void Actor::addComponent(Component* component){
	components.emplace_back(component);
	sort(components.begin(), components.end(), [](Component *x, Component *y){return x->getUpdateOrder() < y->getUpdateOrder();});
}

/**********************************************************************
	removeComponent

	�w�肵���R���|�[�l���g���폜����
**********************************************************************/
void Actor::removeComponent(Component* component){
	auto iterator = std::find(components.begin(), components.end(), component);
	if(iterator != components.end()){
		std::iter_swap(iterator, components.end() - 1);
		components.pop_back();
	}
}
