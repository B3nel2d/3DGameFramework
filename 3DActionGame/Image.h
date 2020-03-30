//======================================================================
//
//	Image
//
//	スプライトに設定する画像を扱うクラス
//
//======================================================================

#pragma once

#define WIN32_LEAN_AND_MEAN

#include "Texture.h"
#include "Math.h"
#include "Settings.h"

class Image{
	protected:
		SpriteData spriteData;
		DWORD colorFilter;
		int columnCount;
		int animationStartFrame;
		int animationEndFrame;
		int animationCurrentFrame;
		float animationFrameDelay;
		float animationTimer;
		bool visible;
		bool loop;
		bool animationCompleted;

		bool initialized;

		Graphics* graphics;
		Texture* texture;

		HRESULT result;

	public:
		Image();
		virtual ~Image();

		virtual bool initialize(Graphics* graphics, const Vector2D& size, int columnCount, Texture* texture);

		virtual void update();

		virtual void draw(DWORD color = Color::white.toDWord());
		virtual void draw(const SpriteData& spriteData, DWORD color = Color::white.toDWord());

		const virtual SpriteData& getSpriteData(){return spriteData;}

		virtual RECT getSpriteDataRectangle(){return spriteData.rectangle;}
		virtual void setSpriteDataRenctagle(RECT rectangle){spriteData.rectangle = rectangle;}

		virtual void setRectangle();

		virtual DWORD getColorFilter(){return colorFilter;}
		virtual void setColorFilter(DWORD color){colorFilter = color;}

		virtual Vector2D getSize(){return spriteData.size;}

		virtual Vector2D getPosition(){return spriteData.position;}
		virtual void setPosition(const Vector2D& position){spriteData.position = position;}

		virtual Vector2D getCenterPosition(){return Vector2D(spriteData.position.x + spriteData.size.x / 2.0f * getScale().x, spriteData.position.x + spriteData.size.x / 2.0f * getScale().y);}
		
		virtual Vector2D getScale(){return spriteData.scale;}
		virtual void setScale(const Vector2D& scale){spriteData.scale = scale;}

		virtual float getRotation(){return spriteData.rotation;}
		virtual void setRotation(float angle){spriteData.rotation = angle;}

		virtual int getAnimationStartFrame(){return animationStartFrame;}
		virtual int getAnimationEndFrame(){return animationEndFrame;}
		virtual void setAnimationCurrentFrame(int startFrame, int endFrame){animationStartFrame = startFrame; animationEndFrame = endFrame;}

		virtual int getAnimationCurrentFrame(){return animationCurrentFrame;}
		virtual void setAnimationCurrentFrame(int value);

		virtual float getFrameDelay(){return animationFrameDelay;}
		virtual void setAnimationFrameDelay(float value){animationFrameDelay = value;}

		virtual bool isVisible(){return visible;}
		virtual void setVisible(bool value){visible = value;}

		virtual void setHorizontalFlip(bool value){spriteData.horizontalFlip = value;}
		virtual void setVerticalFlip(bool value){spriteData.verticalFlip = value;}

		virtual void setLoop(bool value){loop = value;}

		virtual bool isAnimationCompleted(){return animationCompleted;}
		virtual void setAnimationCompleted(bool value){animationCompleted = value;}

		virtual void setTexture(Texture *texture){this->texture = texture;}
};
