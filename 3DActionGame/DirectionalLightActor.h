#pragma once

#include "Actor.h"
#include <d3dx9.h>
#include "Color.h"
#include "Math.h"

class DirectionalLightActor : public Actor{
	private:
		D3DLIGHT9 lightSettings;
		Color lightDiffuseColor;
		Vector3D lightDirection;

		class TransformComponent* transform;

		void initializeLight();

	public:
		DirectionalLightActor(class Level* level);
		~DirectionalLightActor();
};

