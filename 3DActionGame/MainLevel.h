//======================================================================
//
//	MainLevel
//
//	ƒTƒ“ƒvƒ‹ƒŒƒxƒ‹
//
//======================================================================

#pragma once

#include "Level.h"

class MainLevel : public Level{
	private:
		class DirectionalLightActor* directionalLight;
		class CameraActor* mainCamera;
		class PlayerActor* player;
		class PlatformActor* platform;
		class FPSTextActor* fpsText;

	public:
		MainLevel();
		virtual ~MainLevel();

		void initialize();

		void update() override;

		class PlatformActor* getPlatform(){return platform;}
};
