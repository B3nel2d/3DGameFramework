#include "Renderer.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "TextComponent.h"
#include "Game.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
Renderer::Renderer(){
	graphics = Game::getInstance()->getGraphics();

	initializeEnvironment();
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
Renderer::~Renderer(){
	releaseResources();
}

/**********************************************************************
	initializeEnvironment

	環境の初期化を行う
**********************************************************************/
void Renderer::initializeEnvironment(){
	graphics->getDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
	graphics->getDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);
}

/**********************************************************************
	addSprite

	指定したスプライトを追加する
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

	指定したスプライトを削除する
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

	指定したメッシュを追加する
**********************************************************************/
void Renderer::addMesh(MeshComponent* mesh){
	meshes.emplace_back(mesh);
}

/**********************************************************************
	removeMesh

	指定したメッシュを削除する
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

	描画を行う
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

	グラフィックデバイス消失の対処を行う
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

	アクターを描画する
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

	全リソースの解放を行う
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

	全リソースのリセットを行う
**********************************************************************/
void Renderer::resetResources(){
	for(SpriteComponent* sprite : sprites){
		sprite->getTexture()->onResetDevice();
	}

    return;
}
