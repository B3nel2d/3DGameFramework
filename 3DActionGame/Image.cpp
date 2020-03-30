#include "Image.h"
#include "Game.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
Image::Image(){
    initialized = false;

	graphics = NULL;
	texture = NULL;

	spriteData.texture = NULL;

	spriteData.size = Vector2D(2, 2);
	spriteData.position = Vector2D(0.0f, 0.0f);
    spriteData.scale = Vector2D(1.0f, 1.0f);
    spriteData.rotation = 0.0f;
    spriteData.rectangle.left = 0;
    spriteData.rectangle.top = 0;
    spriteData.rectangle.right = (LONG)spriteData.size.x;
    spriteData.rectangle.bottom = (LONG)spriteData.size.y;

	colorFilter = Color::white.toDWord();
	columnCount = 1;

    animationStartFrame = 0;
    animationEndFrame = 0;
    animationCurrentFrame = 0;
    animationFrameDelay = 1.0;
    animationTimer = 0.0;
    
    spriteData.horizontalFlip = false;
    spriteData.verticalFlip = false;

    visible = true;
    loop = true;
    animationCompleted = false;
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
Image::~Image(){

}

/**********************************************************************
	initialize

	初期化を行う
**********************************************************************/
bool Image::initialize(Graphics* graphics, const Vector2D& size, int columnCount, Texture* texture){
    try{
        this->graphics = graphics;
        this->texture = texture;

        spriteData.texture = texture->getTextureData();

		Vector2D spriteSize = size;
		if(spriteSize.x == 0){
			spriteSize.x = (float)texture->getWidth();
		}
		if(spriteSize.y == 0){
			spriteSize.y = (float)texture->getHeight();
		}
		spriteData.size.x = spriteSize.x;
		spriteData.size.y = spriteSize.y;

        this->columnCount = columnCount;
        if(this->columnCount == 0){
            this->columnCount = 1;
		}

        spriteData.rectangle.left = (LONG)((animationCurrentFrame % this->columnCount) * spriteData.size.x);
        spriteData.rectangle.right = (LONG)(spriteData.rectangle.left + spriteData.size.x);
        spriteData.rectangle.top = (LONG)((animationCurrentFrame / this->columnCount) * spriteData.size.y);
        spriteData.rectangle.bottom = (LONG)(spriteData.rectangle.top + spriteData.size.y);
    }
    catch(...){
		return false;
	}

    initialized = true;
    return true;
}

/**********************************************************************
	draw

	画像の描画を行う
**********************************************************************/
void Image::draw(DWORD color){
    if(graphics == NULL || !visible){
        return;
	}

    spriteData.texture = texture->getTextureData();

    graphics->drawSprite(spriteData, color);
}
void Image::draw(const SpriteData& spriteData, DWORD color){
    if(graphics == NULL || !visible){
        return;
	}

    this->spriteData.rectangle = spriteData.rectangle;
    this->spriteData.texture = texture->getTextureData();
	
	graphics->drawSprite(spriteData, color);
}

/**********************************************************************
	update

	毎フレームでの処理を行う
**********************************************************************/
void Image::update(){
    if(0 < animationEndFrame - animationStartFrame){
        animationTimer += Game::getInstance()->getFrameDeltaTime();

        if(animationFrameDelay < animationTimer){
            animationTimer -= animationFrameDelay;
            animationCurrentFrame++;

            if(animationCurrentFrame < animationStartFrame || animationEndFrame < animationCurrentFrame){
                if(loop == true){
                    animationCurrentFrame = animationStartFrame;
				}
                else{
                    animationCurrentFrame = animationEndFrame;
                    animationCompleted = true;
                }
            }

            setRectangle();
        }
    }
}

/**********************************************************************
	setRectangle

	長方形の設定を行う
**********************************************************************/
inline void Image::setRectangle(){
    spriteData.rectangle.left = (LONG)((animationCurrentFrame % columnCount) * spriteData.size.x);
    spriteData.rectangle.right = (LONG)(spriteData.rectangle.left + spriteData.size.x);
    spriteData.rectangle.top = (LONG)((animationCurrentFrame / columnCount) * spriteData.size.y);
    spriteData.rectangle.bottom = (LONG)(spriteData.rectangle.top + spriteData.size.y);
}

/**********************************************************************
	setAnimationCurrentFrame

	アニメーションの現在のフレームを設定する
**********************************************************************/
void Image::setAnimationCurrentFrame(int value){
    if(value >= 0){
        animationCurrentFrame = value;
        animationCompleted = false;
        setRectangle();
    }
}
