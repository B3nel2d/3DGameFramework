#include "TransformComponent.h"

/**********************************************************************
	�R���X�g���N�^�[
**********************************************************************/
TransformComponent::TransformComponent(Actor* owner) : Component(owner){
	position = Vector3D::zero;
	rotation = Quaternion::identity;
	scale_ = Vector3D(1.0f, 1.0f, 1.0f);
}

/**********************************************************************
	�f�R���X�g���N�^�[
**********************************************************************/
TransformComponent::~TransformComponent(){

}

/**********************************************************************
	translate

	�ړ���K�p����
**********************************************************************/
void TransformComponent::translate(const Vector3D& position){
	this->position.x += position.x;
	this->position.y += position.y;
	this->position.z += position.z;
}
void TransformComponent::translate(float x, float y, float z){
	this->position.x += x;
	this->position.y += y;
	this->position.z += z;
}

/**********************************************************************
	rotate

	��]��K�p����
**********************************************************************/
void TransformComponent::rotate(const Quaternion& rotation){
	this->rotation = this->rotation * rotation;
}
void TransformComponent::rotate(float angle, const Vector3D& axis){
	this->rotation = this->rotation * Quaternion(angle, axis);
}

/**********************************************************************
	scale

	�g��k����K�p����
**********************************************************************/
void TransformComponent::scale(const Vector3D& scale){
	this->scale_.x *= scale.x;
	this->scale_.y *= scale.y;
	this->scale_.z *= scale.z;
}
void TransformComponent::scale(float x, float y, float z){
	this->scale_.x *= x;
	this->scale_.y *= y;
	this->scale_.z *= z;
}

/**********************************************************************
	update

	���t���[���ł̏������s��
**********************************************************************/
void TransformComponent::update(){
	
}

void TransformComponent::setPosition(const Vector3D& position){
	this->position = position;
}

void TransformComponent::setPosition(float x, float  y, float z){
	this->position = Vector3D(x, y, z);
}

void TransformComponent::setRotation(const Quaternion& rotation){
	this->rotation = rotation;
}

void TransformComponent::setRotation(float angle, const Vector3D& axis){
	this->rotation = Quaternion(angle, axis);
}

void TransformComponent::setScale(const Vector3D& scale){
	this->scale_ = scale;
}

void TransformComponent::setScale(float x, float  y, float z){
	this->scale_ = Vector3D(x, y, z);
}
