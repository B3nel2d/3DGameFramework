//======================================================================
//
//	
//
//	ê‡ñæ
//
//======================================================================

#pragma once

#include "Actor.h"

class BackgroundActor : public Actor{
	private:
		class TransformComponent* transform;
		class SpriteComponent* sprite;

	public:
		BackgroundActor(Level* level);
		~BackgroundActor();

		void update();

		class TransformComponent* getTransform(){return transform;}
		class SpriteComponent* getSprite(){return sprite;}
};
