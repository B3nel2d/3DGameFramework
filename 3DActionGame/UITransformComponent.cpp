#include "UITransformComponent.h"
#include "Actor.h"
#include "Settings.h"

/**********************************************************************
	�R���X�g���N�^�[
**********************************************************************/
UITransformComponent::UITransformComponent(Actor* owner) : Component(owner){
	size = Vector2D(UNIT, UNIT);
	position = Vector2D::zero;
	rotation = 0.0f;
}

/**********************************************************************
	�f�R���X�g���N�^�[
**********************************************************************/
UITransformComponent::~UITransformComponent(){

}

/**********************************************************************
	translate

	�ړ���K�p����
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

	��]��K�p����
**********************************************************************/
void UITransformComponent::rotate(float rotation){
	this->rotation += rotation;
}

/**********************************************************************
	update

	���t���[���ł̏������s��
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
