#pragma once

#include "Actor.h"

class FPSTextActor : public Actor{
	private:
		class UITransformComponent* uiTransform;
		class TextComponent* text;

	public:
		FPSTextActor(class Level* level);
		~FPSTextActor();

		void update();

		class UITransformComponent* getUITransform(){return uiTransform;}
		class TextComponent* getText(){return text;}
};
