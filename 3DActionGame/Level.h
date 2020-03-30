//======================================================================
//
//	Level
//
//	ƒŒƒxƒ‹‚ÌŠî’êƒNƒ‰ƒX
//
//======================================================================

#pragma once

#define WIN32_LEAN_AND_MEAN

#include "Level.h"
#include "Physics.h"
#include "Renderer.h"

class Level{
	private:
		Physics* physics;
		Renderer* renderer;

		vector<class Actor*> actors;
		vector<class Actor*> pendingActors;

		bool updatingActors;

	public:
		Level();
		virtual ~Level();

		virtual void initialize() = 0;

		void addActor(class Actor* actor);
		void removeActor(class Actor* actor);

		virtual void update();
		void detectCollisions();
		void render();

		void deleteResources();

		Physics* getPhysics(){return physics;}
		Renderer* getRenderer(){return renderer;}
};
