#include "Texture.h"
#include "Color.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
Texture::Texture(){
    textureData = NULL;
	fileName = NULL;
    width = 0;
    height = 0;
    
	initialized = false;
    graphics = NULL;
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
Texture::~Texture(){
    releaseResource(textureData);
}

/**********************************************************************
	initialize

	初期化を行う
**********************************************************************/
bool Texture::initialize(Graphics* graphics, const char* fileName){
    try{
        this->graphics = graphics;
        this->fileName = fileName;

        result = graphics->loadTexture(fileName, TRANSPARENT_COLOR, width, height, textureData);
        if(FAILED(result)){
            releaseResource(textureData);
            return false;
        }
    }
    catch(...){
		return false;
	}
    
	initialized = true;
    return true;
}

/**********************************************************************
	onLostDevice

	グラフィックデバイス消失時の対応を行う
**********************************************************************/
void Texture::onLostDevice(){
	if(!initialized){
		return;
	}
    
	releaseResource(textureData);
}

/**********************************************************************
	onResetDevice

	グラフィックデバイスリセット時の対応を行う
**********************************************************************/
void Texture::onResetDevice(){
	if(!initialized){
        return;
	}

    graphics->loadTexture(fileName, TRANSPARENT_COLOR, width, height, textureData);
}
