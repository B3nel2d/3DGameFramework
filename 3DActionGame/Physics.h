//======================================================================
//
//	Physics
//
//	���x�����̃R���C�_�[���Ǘ�������������Փ˔�����s���N���X
//
//======================================================================

#pragma once

#define WIN32_LEAN_AND_MEAN

#include <vector>
#include <functional>
#include "Collision.h"

using namespace std;

class Physics{
	private:
		vector<class BoxColliderComponent*> colliders;

	public:
		Physics();
		~Physics();

		void addCollider(class BoxColliderComponent* collider);
		void removeCollider(class BoxColliderComponent* collider);

		void detectCollisions();

		bool castLineSegment(const LineSegment& lineSegment, CollisionInformation& collision_out);

		void testPairwise(std::function<void(class Actor*, class Actor*)> function);
		void testSweepAndPrune(std::function<void(class Actor*, class Actor*)> function);

		void deleteResources();
};
