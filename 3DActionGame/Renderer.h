//======================================================================
//
//	Renderer
//
//	レベル毎のグラフィックスを管理しアクターの描画を行うクラス
//
//======================================================================

#pragma once

#define WIN32_LEAN_AND_MEAN

#include <vector>
#include <unordered_map>
#include "Graphics.h"

using namespace std;

class Renderer{
	private:
		HRESULT result;

		Graphics* graphics;

		vector<class SpriteComponent*> sprites;
		vector<class MeshComponent*> meshes;

		void initializeEnvironment();

	public:
		Renderer();
		virtual ~Renderer();

		void addSprite(class SpriteComponent* sprite);
		void removeSprite(class SpriteComponent* sprite);

		void addMesh(class MeshComponent* mesh);
		void removeMesh(class MeshComponent* mesh);

		void render();
		void renderActors();
		void handleLostGraphicsDevice();

		void releaseResources();
		void resetResources();
};
