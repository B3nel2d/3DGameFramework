#include "Level.h"
#include "Actor.h"
#include "Game.h"
#include "Settings.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
Level::Level(){
	physics = new Physics();
	renderer = new Renderer();

	updatingActors = false;
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
Level::~Level(){
	deleteResources();
}

/**********************************************************************
	addActor

	指定したアクターを追加する
**********************************************************************/
void Level::addActor(Actor* actor){
	if(updatingActors){
		pendingActors.emplace_back(actor);
	}
	else{
		actors.emplace_back(actor);
	}
}

/**********************************************************************
	removeActor

	指定したアクターを削除する
**********************************************************************/
void Level::removeActor(Actor* actor){
	auto iterator = std::find(actors.begin(), actors.end(), actor);
	if(iterator != actors.end()){
		std::iter_swap(iterator, actors.end() - 1);
		actors.pop_back();
	}

	iterator = std::find(pendingActors.begin(), pendingActors.end(), actor);
	if(iterator != pendingActors.end()){
		std::iter_swap(iterator, pendingActors.end() - 1);
		pendingActors.pop_back();
	}
}

/**********************************************************************
	update

	毎フレームでの処理を行う
**********************************************************************/
void Level::update(){
	updatingActors = true;
	for(Actor* actor : actors){
		actor->update();
	}
	updatingActors = false;

	for(Actor* actor : pendingActors){
		actors.emplace_back(actor);
	}
	pendingActors.clear();

	vector<Actor*> deletedActors;
	for(Actor* actor : actors){
		if(actor->getState() == Actor::deleted){
			deletedActors.emplace_back(actor);
		}
	}

	for(Actor* actor : deletedActors){
		delete actor;
	}
}

/**********************************************************************
	detectCollisions

	衝突判定を行う
**********************************************************************/
void Level::detectCollisions(){
	physics->detectCollisions();
}

/**********************************************************************
	render

	描画を行う
**********************************************************************/
void Level::render(){
	renderer->render();
}

/**********************************************************************
	deleteResources

	全てのリソースを削除する
**********************************************************************/
void Level::deleteResources(){
	deleteResource(physics);
    deleteResource(renderer);

	while(!actors.empty()){
		delete actors.back();
	}
}
