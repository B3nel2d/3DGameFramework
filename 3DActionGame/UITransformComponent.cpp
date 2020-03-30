#include "UITransformComponent.h"
#include "Actor.h"
#include "Settings.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
UITransformComponent::UITransformComponent(Actor* owner) : Component(owner){
	size = Vector2D(UNIT, UNIT);
	position = Vector2D::zero;
	rotation = 0.0f;
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
UITransformComponent::~UITransformComponent(){

}

/**********************************************************************
	translate

	移動を適用する
**********************************************************************/
void UITransformComponent::translate(const Vector2D& position){
	this->position.x += position.x;
	this->position.y += position.y;
}
void UITransformComponent::translate(float x, float y){
	this->position.x += x;
	this->position.y += y;
}

/**********************************************************************
	rotate

	回転を適用する
**********************************************************************/
void UITransformComponent::rotate(float rotation){
	this->rotation += rotation;
}

/**********************************************************************
	update

	毎フレームでの処理を行う
**********************************************************************/
void UITransformComponent::update(){
	
}

void UITransformComponent::setSize(const Vector2D& size){
	this->size = size;
}

void UITransformComponent::setSize(float x, float  y){
	this->size = Vector2D(x, y);
}

void UITransformComponent::setPosition(const Vector2D& position){
	this->position = position;
}

void UITransformComponent::setPosition(float x, float  y){
	this->position = Vector2D(x, y);
}

void UITransformComponent::setRotation(float rotation){
	this->rotation = rotation;
}
