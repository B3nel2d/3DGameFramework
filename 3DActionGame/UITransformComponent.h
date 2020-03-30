//======================================================================
//
//	UITransformComponent
//
//	UIアクターの座標・回転・拡大縮小を扱うコンポーネントクラス
//
//======================================================================

#pragma once

#include "Component.h"
#include "Math.h"

class UITransformComponent : public Component{
	private:
		Vector2D size;
		Vector2D position;
		float rotation;

	public:
		UITransformComponent(class Actor* owner);
		~UITransformComponent();

		void update();

		void translate(const Vector2D& position);
		void translate(float x, float y);

		void rotate(float rotation);

		Vector2D getSize(){return size;}
		void setSize(const Vector2D& size);
		void setSize(float x, float y);

		Vector2D getPosition(){return position;}
		void setPosition(const Vector2D& position);
		void setPosition(float x, float y);

		float getRotation(){return rotation;}
		void setRotation(float rotation);
};
