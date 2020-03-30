#include "Texture.h"
#include "Color.h"

/**********************************************************************
	�R���X�g���N�^�[
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
	�f�R���X�g���N�^�[
**********************************************************************/
Texture::~Texture(){
    releaseResource(textureData);
}

/**********************************************************************
	initialize

	���������s��
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

	�O���t�B�b�N�f�o�C�X�������̑Ή����s��
**********************************************************************/
void Texture::onLostDevice(){
	if(!initialized){
		return;
	}
    
	releaseResource(textureData);
}

/**********************************************************************
	onResetDevice

	�O���t�B�b�N�f�o�C�X���Z�b�g���̑Ή����s��
**********************************************************************/
void Texture::onResetDevice(){
	if(!initialized){
        return;
	}

    graphics->loadTexture(fileName, TRANSPARENT_COLOR, width, height, textureData);
}
