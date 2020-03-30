#include "Physics.h"
#include <algorithm>
#include "BoxColliderComponent.h"
#include "Actor.h"

#include <windows.h>

/**********************************************************************
	コンストラクター
**********************************************************************/
Physics::Physics(){

}

/**********************************************************************
	デコンストラクター
**********************************************************************/
Physics::~Physics(){
	deleteResources();
}

/**********************************************************************
	addCollider

	指定したコライダーを追加する
**********************************************************************/
void Physics::addCollider(class BoxColliderComponent* collider){
	colliders.emplace_back(collider);
}

/**********************************************************************
	removeCollider

	指定したコライダーを削除する
**********************************************************************/
void Physics::removeCollider(class BoxColliderComponent* collider){
	auto iterator = std::find(colliders.begin(), colliders.end(), collider);
	if(iterator != colliders.end()){
		std::iter_swap(iterator, colliders.end() - 1);
		colliders.pop_back();
	}
}


void Physics::detectCollisions(){

}

/**********************************************************************
	castLineSegment

	線分キャストを行う
**********************************************************************/
bool Physics::castLineSegment(const LineSegment& lineSegment, CollisionInformation& collision_out){
	bool collided = false;
	float closestT = Math::positiveInfinity;
	Vector3D normal;

	for(BoxColliderComponent* collider : colliders){
		float t;

		if(intersect(lineSegment, collider->getWorldCollision(), t, normal)){
			if(t < closestT){
				collision_out.point = lineSegment.getPoint(t);
				collision_out.normal = normal;
				collision_out.collider = collider;
				collision_out.actor = collider->getOwner();

				collided = true;
			}
		}
	}

	return collided;
}

/**********************************************************************
	testPairwise

	全ての衝突に対して指定した処理を行う(全てのアクター同士で行う)
**********************************************************************/
void Physics::testPairwise(std::function<void(Actor*, Actor*)> function){
	for(size_t i = 0; i < colliders.size(); i++){
		for(size_t j = i + 1; j < colliders.size(); j++){
			BoxColliderComponent* a = colliders[i];
			BoxColliderComponent* b = colliders[j];

			if(intersect(a->getWorldCollision(), b->getWorldCollision())){
				function(a->getOwner(), b->getOwner());
			}
		}
	}
}

/**********************************************************************
	testSweepAndPrune

	全ての衝突に対して指定した処理を行う(スイープ&プルーン)
**********************************************************************/
void Physics::testSweepAndPrune(std::function<void(class Actor*, class Actor*)> function){
	std::sort(
		colliders.begin(),
		colliders.end(),
		[](BoxColliderComponent* a, BoxColliderComponent* b){
			return a->getWorldCollision().minimumPoint.x < b->getWorldCollision().minimumPoint.x;
		}
	);

	for(size_t i = 0; i < colliders.size(); i++){
		BoxColliderComponent* a = colliders[i];
		float max = a->getWorldCollision().maximumPoint.x;
		for(size_t j = i + 1; j < colliders.size(); j++){
			BoxColliderComponent* b = colliders[j];

			if(max < b->getWorldCollision().minimumPoint.x){
				break;
			}
			else if(intersect(a->getWorldCollision(), b->getWorldCollision())){
				function(a->getOwner(), b->getOwner());
			}
		}
	}
}

/**********************************************************************
	deleteResources

	全リソースの削除を行う
**********************************************************************/
void Physics::deleteResources(){
	while(!colliders.empty()){
		delete colliders.back();
	}
}
