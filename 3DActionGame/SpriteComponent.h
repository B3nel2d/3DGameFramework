//======================================================================
//
//	SpriteComponent
//
//	スプライトを設定し表示するコンポーネントクラス
//
//======================================================================

#pragma once

#include "Component.h"
#include "Texture.h"
#include "Image.h"

class SpriteComponent : public Component{
	private:
		Texture texture;
		Image image;

		class TransformComponent* transform;

	protected:
		int drawOrder;

	public:
		SpriteComponent(class Actor* owner, class Level* level);
		~SpriteComponent();

		virtual bool initialize(class Graphics* graphics, const char* fileName, int drawOrder = 0);

		virtual void update();
		virtual void draw();

		Texture* getTexture(){return &texture;}

		Image* getImage(){return &image;}

		int getDrawOrder(){return drawOrder;};
};
