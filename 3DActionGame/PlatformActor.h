#pragma once

#include "Actor.h"

class PlatformActor : public Actor{
	private:
		class TransformComponent* transform;
		class MeshComponent* mesh;
		class BoxColliderComponent* boxCollider;

	public:
		PlatformActor(Level* level);
		virtual ~PlatformActor();

		class TransformComponent* getTransform(){return transform;}
		class MeshComponent* getMesh(){return mesh;}
		class BoxColliderComponent* getBoxCollider(){return boxCollider;}
};
