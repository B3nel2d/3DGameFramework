#include "MainLevel.h"
#include "DirectionalLightActor.h"
#include "Actor.h"
#include "CameraActor.h"
#include "PlayerActor.h"
#include "PlatformActor.h"
#include "FPSTextActor.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "UITransformComponent.h"
#include "MeshComponent.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "BoxColliderComponent.h"
#include "Game.h"
#include "Collision.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
MainLevel::MainLevel(){
	directionalLight = nullptr;
	mainCamera = nullptr;
	player = nullptr;
	platform = nullptr;
	fpsText = nullptr;
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
MainLevel::~MainLevel(){

}

/**********************************************************************
	initialize

	レベルの初期化を行う
**********************************************************************/
void MainLevel::initialize(){
	directionalLight = new DirectionalLightActor(Game::getInstance()->getLevel("Main Level"));

	mainCamera = new CameraActor(Game::getInstance()->getLevel("Main Level"));
	mainCamera->getTransform()->setPosition(0, 0, -15);
	Game::getInstance()->getGraphics()->setActiveCamera(mainCamera->getCamera());

	player = new PlayerActor(Game::getInstance()->getLevel("Main Level"));
	player->setTag(Actor::Tag::player);
	player->getTransform()->setPosition(Vector3D::zero);

	platform = new PlatformActor(Game::getInstance()->getLevel("Main Level"));
	platform->setTag(Actor::Tag::platform);
	platform->getTransform()->setPosition(Vector3D(0, -2.5f, 0));
	platform->getTransform()->setScale(Vector3D(3, 1, 1));

	fpsText = new FPSTextActor(Game::getInstance()->getLevel("Main Level"));
	fpsText->getText()->initialize(Game::getInstance()->getGraphics(), "Arial", 50, false, false, 2);
	fpsText->getText()->setFormat(TextComponent::Format::singleLine | TextComponent::Format::verticalCenter | TextComponent::Format::horizontalCenter);
	fpsText->getUITransform()->setSize(125, 50);
	fpsText->getUITransform()->setPosition(WINDOW_WIDTH - 75, 25);
}

/**********************************************************************
	update

	毎フレームでの処理を行う
**********************************************************************/
void MainLevel::update(){
	Level::update();

	if(intersect(player->getBoxCollider()->getWorldCollision(), platform->getBoxCollider()->getWorldCollision())){
		OutputDebugString("COLLIDED\n");
	}
	
	getPhysics()->testPairwise(
		[](Actor* a, Actor* b){
			//OutputDebugString("COLLIDED\n");
		}
	);
}
