//======================================================================
//
//	CameraActor
//
//	カメラ用アクター
//
//======================================================================

#pragma once

#include "Actor.h"
#include "Math.h"

class CameraActor : public Actor{
	private:
		class CameraComponent* camera;
		class TransformComponent* transform;

	public:
		CameraActor(class Level* level);
		virtual ~CameraActor();

		class CameraComponent* getCamera(){return camera;}
		class TransformComponent* getTransform(){return transform;}
};
