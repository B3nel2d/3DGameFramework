//======================================================================
//
//	TextComponent
//
//	テキストを設定し表示するコンポーネントクラス
//
//======================================================================

#pragma once

#include "SpriteComponent.h"
#include "Text.h"

class TextComponent : public SpriteComponent{
	public:
		enum Format{
			top = DT_TOP,
			verticalCenter = DT_VCENTER,
			bottom = DT_BOTTOM,
			left = DT_LEFT,
			horizontalCenter = DT_CENTER,
			right = DT_RIGHT,
			singleLine = DT_SINGLELINE
		};

	private:
		Text text;

		std::string string;
		UINT format;

		class UITransformComponent* uiTransform;

	public:
		TextComponent(class Actor* owner, class Level* level);
		~TextComponent();

		bool initialize(class Graphics* graphics, const char* fontName, int size, bool bold, bool italic, int drawOrder);

		void update();
		void draw();

		Text* getText(){return &text;}

		const std::string& getString(){return this->string;}
		void setString(const std::string& string){this->string = string;}

		void setFormat(UINT format){this->format = format;}
};
