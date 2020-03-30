//======================================================================
//
//	CameraComponent
//
//	カメラのコンポーネント
//
//======================================================================

#pragma once

#include "Component.h"
#include "Math.h"
#include "Color.h"

class CameraComponent : public Component{
	private:
		class TransformComponent* transform;

		Vector3D lookPosition;
		Vector3D upVector;

		float fieldOfView;
		float nearClippingPlaneDistance;
		float farClippingPlaneDistance;

		Color backgroundColor;

	public:
		CameraComponent(class Actor* owner, class TransformComponent* transform);
		virtual ~CameraComponent();

		class TransformComponent* getTransform(){return transform;}

		Vector3D getLookPosition(){return lookPosition;}
		void setLookPosition(const Vector3D& position){lookPosition = position;}

		Vector3D getUpVector(){return upVector;}
		void setUpVector(const Vector3D& vector){upVector = vector;}

		float getFieldOfView(){return fieldOfView;}
		void setFieldOfView(float value){fieldOfView = value;}

		float getNearClippingPlaneDistance(){return nearClippingPlaneDistance;}
		void setNearClippingPlaneDistance(float value){nearClippingPlaneDistance = value;}

		float getFarClippingPlaneDistance(){return farClippingPlaneDistance;}
		void setFarClippingPlaneDistance(float value){farClippingPlaneDistance = value;}

		Color getBackgroundColor(){return backgroundColor;}
		void setBackgroundColor(const Color& color){backgroundColor = color;}
};
