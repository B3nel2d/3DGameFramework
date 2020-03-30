#include "Actor.h"
#include <algorithm>
#include "Game.h"
#include "Level.h"
#include "Component.h"
#include "Settings.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
Actor::Actor(class Level* level){
	state = active;
	tag = none;

	this->level = level;
	level->addActor(this);
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
Actor::~Actor(){
	level->removeActor(this);

	while(!components.empty()){
		delete components.back();
	}
}

/**********************************************************************
	update

	毎フレームでの処理を行う
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

	指定したコンポーネントを追加する
**********************************************************************/
void Actor::addComponent(Component* component){
	components.emplace_back(component);
	sort(components.begin(), components.end(), [](Component *x, Component *y){return x->getUpdateOrder() < y->getUpdateOrder();});
}

/**********************************************************************
	removeComponent

	指定したコンポーネントを削除する
**********************************************************************/
void Actor::removeComponent(Component* component){
	auto iterator = std::find(components.begin(), components.end(), component);
	if(iterator != components.end()){
		std::iter_swap(iterator, components.end() - 1);
		components.pop_back();
	}
}
