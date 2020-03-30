#include "Renderer.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "TextComponent.h"
#include "Game.h"

/**********************************************************************
	�R���X�g���N�^�[
**********************************************************************/
Renderer::Renderer(){
	graphics = Game::getInstance()->getGraphics();

	initializeEnvironment();
}

/**********************************************************************
	�f�R���X�g���N�^�[
**********************************************************************/
Renderer::~Renderer(){
	releaseResources();
}

/**********************************************************************
	initializeEnvironment

	���̏��������s��
**********************************************************************/
void Renderer::initializeEnvironment(){
	graphics->getDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
	graphics->getDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);
}

/**********************************************************************
	addSprite

	�w�肵���X�v���C�g��ǉ�����
**********************************************************************/
void Renderer::addSprite(SpriteComponent* sprite){
	auto iterator = sprites.begin();
	for(; iterator != sprites.end(); ++iterator){
		if(sprite->getDrawOrder() < (*iterator)->getDrawOrder()){
			break;
		}
	}

	sprites.insert(iterator, sprite);
}

/**********************************************************************
	removeSprite

	�w�肵���X�v���C�g���폜����
**********************************************************************/
void Renderer::removeSprite(SpriteComponent* sprite){
	auto iterator = std::find(sprites.begin(), sprites.end(), sprite);
	if(iterator != sprites.end()){
		std::iter_swap(iterator, sprites.end() - 1);
		sprites.pop_back();
	}
}

/**********************************************************************
	addMesh

	�w�肵�����b�V����ǉ�����
**********************************************************************/
void Renderer::addMesh(MeshComponent* mesh){
	meshes.emplace_back(mesh);
}

/**********************************************************************
	removeMesh

	�w�肵�����b�V�����폜����
**********************************************************************/
void Renderer::removeMesh(MeshComponent* mesh){
	auto iterator = std::find(meshes.begin(), meshes.end(), mesh);
	if(iterator != meshes.end()){
		std::iter_swap(iterator, meshes.end() - 1);
		meshes.pop_back();
	}
}

/**********************************************************************
	render

	�`����s��
**********************************************************************/
void Renderer::render(){
    if(SUCCEEDED(graphics->beginScene())){
		renderActors();

        graphics->endScene();
    }
    handleLostGraphicsDevice();

    graphics->showBackBuffer();
}

/**********************************************************************
	handleLostGraphicsDevice

	�O���t�B�b�N�f�o�C�X�����̑Ώ����s��
**********************************************************************/
void Renderer::handleLostGraphicsDevice(){
    result = graphics->getDeviceState();

    if(FAILED(result)){
        if(result == D3DERR_DEVICELOST){
            Sleep(100);
            return;
        }
        else if(result == D3DERR_DEVICENOTRESET){
            releaseResources();

            result = graphics->reset();
			if(FAILED(result)){
				return;
			}

            resetResources();
        }
		else{
			return;
		}
    }
}

/**********************************************************************
	renderActors

	�A�N�^�[��`�悷��
**********************************************************************/
void Renderer::renderActors(){
	for(auto mesh : meshes){
		mesh->draw();
	}

    graphics->beginSpriteDraw();

	for(auto sprite : sprites){
		sprite->draw();
	}

    graphics->endSpriteDraw();
}

/**********************************************************************
	releaseResources

	�S���\�[�X�̉�����s��
**********************************************************************/
void Renderer::releaseResources(){
	for(SpriteComponent* sprite : sprites){
		sprite->getTexture()->onLostDevice();
	}
	for(MeshComponent* mesh : meshes){
		mesh->getMesh().deleteResources();
	}

	return;
}

/**********************************************************************
	resetResources

	�S���\�[�X�̃��Z�b�g���s��
**********************************************************************/
void Renderer::resetResources(){
	for(SpriteComponent* sprite : sprites){
		sprite->getTexture()->onResetDevice();
	}

    return;
}
