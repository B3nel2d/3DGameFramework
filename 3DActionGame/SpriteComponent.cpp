#include "SpriteComponent.h"
#include <typeinfo>
#include "Game.h"
#include "Level.h"
#include "Actor.h"
#include "Texture.h"
#include "Image.h"
#include "TransformComponent.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
SpriteComponent::SpriteComponent(Actor* owner, Level* level) : Component(owner){
	transform = owner->getComponent<TransformComponent>();
	level->getRenderer()->addSprite(this);
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
SpriteComponent::~SpriteComponent(){
	owner->getLevel()->getRenderer()->removeSprite(this);
}

/**********************************************************************
	initialize

	初期化を行う
**********************************************************************/
bool SpriteComponent::initialize(class Graphics* graphics, const char* fileName, int drawOrder){
    if(!texture.initialize(graphics, fileName)){
        OutputDebugString("Error: Failed to initialize a texture.\n");
		return false;
	}
	if(!image.initialize(graphics, Vector2D::zero, 0, &texture)){
		OutputDebugString("Error: Failed to initialize an image.\n");
		return false;
	}

	this->drawOrder = drawOrder;

	return true;
}

/**********************************************************************
	update

	毎フレームでの処理を行う
**********************************************************************/
void SpriteComponent::update(){
	Component::update();

	if(transform){
		image.setPosition(Vector2D(transform->getPosition().x - image.getSize().x * transform->getScale().x * 0.5f, transform->getPosition().y - image.getSize().y * transform->getScale().y * 0.5f));
		image.setRotation(transform->getRotation().toEulerAngles().z);
		image.setScale(Vector2D(transform->getScale().x, transform->getScale().y));	
	}
}

/**********************************************************************
	draw

	描画を行う
**********************************************************************/
void SpriteComponent::draw(){
	image.draw();
}
