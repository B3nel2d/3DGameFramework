#pragma once

#include "Actor.h"

class PlayerActor : public Actor{
	private:
		class TransformComponent* transform;
		class MeshComponent* mesh;
		class BoxColliderComponent* boxCollider;

		float movementSpeed;

	public:
		PlayerActor(Level* level);
		~PlayerActor();

		void update();

		class TransformComponent* getTransform(){return transform;}
		class MeshComponent* getMesh(){return mesh;}
		class BoxColliderComponent* getBoxCollider(){return boxCollider;}
};
