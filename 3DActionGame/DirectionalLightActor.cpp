#include "DirectionalLightActor.h"
#include "TransformComponent.h"
#include "Game.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
DirectionalLightActor::DirectionalLightActor(Level* level) : Actor(level){
	transform = new TransformComponent(this);

	lightDiffuseColor = Color(1.5f, 1.5f, 1.5f);
	lightDirection = Vector3D(1, -1, 1).getNormalized();

	initializeLight();
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
DirectionalLightActor::~DirectionalLightActor(){

}

/**********************************************************************
	initializeLight

	ライトの初期化を行う
**********************************************************************/
void DirectionalLightActor::initializeLight(){
	Graphics* graphics = Game::getInstance()->getGraphics();

	ZeroMemory(&lightSettings, sizeof(D3DLIGHT9));
	lightSettings.Type = D3DLIGHT_DIRECTIONAL;
	lightSettings.Diffuse.r = lightDiffuseColor.r;
	lightSettings.Diffuse.g = lightDiffuseColor.g;
	lightSettings.Diffuse.b = lightDiffuseColor.b;
	lightSettings.Direction = lightDirection.toD3DXVECTOR3();
	lightSettings.Range = 1000.0f;

	graphics->getDevice()->SetLight(0, &lightSettings);
	graphics->getDevice()->LightEnable(0, TRUE);

	Color ambientLightColor = Color(0.5f, 0.5f, 0.5f);
	graphics->getDevice()->SetRenderState(D3DRS_AMBIENT, ambientLightColor.toDWord());
}
