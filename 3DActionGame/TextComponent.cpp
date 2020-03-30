#include "TextComponent.h"
#include "Actor.h"
#include "Level.h"
#include "UITransformComponent.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
TextComponent::TextComponent(Actor* owner, Level* level) : SpriteComponent(owner, level){
	uiTransform = owner->getComponent<UITransformComponent>();
	level->getRenderer()->addSprite(this);

	string = "";
	format = TextComponent::Format::top | TextComponent::Format::left;
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
TextComponent::~TextComponent(){
	owner->getLevel()->getRenderer()->removeSprite(this);
}

/**********************************************************************
	initialize

	初期化を行う
**********************************************************************/
bool TextComponent::initialize(class Graphics* graphics, const char* fontName, int size, bool bold, bool italic, int drawOrder = 0){
    if(!text.initialize(graphics, fontName, size, bold, italic)){
        OutputDebugString("Error: Failed to initialize a text.\n");
		return false;
	}

	this->drawOrder = drawOrder;

	return true;
}

/**********************************************************************
	update

	毎フレームでの処理を行う
**********************************************************************/
void TextComponent::update(){
	Component::update();

	if(uiTransform){
		text.setPosition(Vector2D(uiTransform->getPosition().x - uiTransform->getSize().x * 0.5f, uiTransform->getPosition().y - uiTransform->getSize().y * 0.5f));
		text.setRotation(uiTransform->getRotation());
	}
}

/**********************************************************************
	draw

	描画を行う
**********************************************************************/
void TextComponent::draw(){
	RECT rectangle;
	rectangle.left = (LONG)(uiTransform->getPosition().x - uiTransform->getSize().x * 0.5f);
	rectangle.right = (LONG)(uiTransform->getPosition().x + uiTransform->getSize().x * 0.5f);
	rectangle.top = (LONG)(uiTransform->getPosition().y - uiTransform->getSize().y * 0.5f);
	rectangle.bottom = (LONG)(uiTransform->getPosition().y + uiTransform->getSize().y * 0.5f);

	text.print(this->string, rectangle, format);
}
