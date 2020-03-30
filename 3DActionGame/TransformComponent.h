//======================================================================
//
//	TransformComponent
//
//	物体の座標・回転・拡大縮小を扱うコンポーネントクラス
//
//======================================================================

#pragma once

#include "Component.h"
#include "Math.h"

class TransformComponent : public Component{
	private:
		Vector3D position;
		Quaternion rotation;
		Vector3D scale_;

	public:
		TransformComponent(class Actor* owner);
		virtual ~TransformComponent();

		void update();

		void translate(const Vector3D& position);
		void translate(float x, float y, float z);

		void rotate(const Quaternion& rotation);
		void rotate(float angle, const Vector3D& axis);

		void scale(const Vector3D& scale);
		void scale(float x, float y, float z);

		Vector3D getPosition(){return position;}
		void setPosition(const Vector3D& position);
		void setPosition(float x, float y, float z);

		Quaternion getRotation(){return rotation;}
		void setRotation(const Quaternion& rotation);
		void setRotation(float angle, const Vector3D& axis);

		Vector3D getScale(){return scale_;}
		void setScale(const Vector3D& scale);
		void setScale(float x, float y, float z);
};
