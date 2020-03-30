#include "Level.h"
#include "Actor.h"
#include "Game.h"
#include "Settings.h"

/**********************************************************************
	�R���X�g���N�^�[
**********************************************************************/
Level::Level(){
	physics = new Physics();
	renderer = new Renderer();

	updatingActors = false;
}

/**********************************************************************
	�f�R���X�g���N�^�[
**********************************************************************/
Level::~Level(){
	deleteResources();
}

/**********************************************************************
	addActor

	�w�肵���A�N�^�[��ǉ�����
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

	�w�肵���A�N�^�[���폜����
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

	���t���[���ł̏������s��
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

	�Փ˔�����s��
**********************************************************************/
void Level::detectCollisions(){
	physics->detectCollisions();
}

/**********************************************************************
	render

	�`����s��
**********************************************************************/
void Level::render(){
	renderer->render();
}

/**********************************************************************
	deleteResources

	�S�Ẵ��\�[�X���폜����
**********************************************************************/
void Level::deleteResources(){
	deleteResource(physics);
    deleteResource(renderer);

	while(!actors.empty()){
		delete actors.back();
	}
}
