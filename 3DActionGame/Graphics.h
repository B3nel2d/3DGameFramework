//======================================================================
//
//	Graphics
//
//	グラフィックス関連の構造体や設定を扱うクラス
//
//======================================================================

#pragma once

#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif

#include <unordered_map>
#include <d3d9.h>
#include <d3dx9.h>
#include "Math.h"
#include "Mesh.h"
#include "Settings.h"

using namespace std;

struct SpriteData{
	LPDIRECT3DTEXTURE9 texture;

    RECT rectangle;

	Vector2D position;
	float rotation;
	Vector2D size;
    Vector2D scale;

    bool horizontalFlip;
    bool verticalFlip;
};

class Graphics{
	private:
		LPDIRECT3D9 direct3D;
		LPDIRECT3DDEVICE9 device;
		D3DPRESENT_PARAMETERS presentationParameters;
		D3DDISPLAYMODE displayMode;

		LPD3DXSPRITE sprite;

		HWND window;

		int width;
		int height;
		DWORD backGroundColor;
		bool fullScreen;

		unordered_map<string, Mesh> meshes;

		class CameraComponent* activeCamera;

		HRESULT result;

		void initializePresentationParameters();

	public:
		Graphics();
		virtual ~Graphics();

		void initialize(HWND window, int width, int height, bool fullscreen);
		void release();

		bool isAdapterCompatible();
		HRESULT reset();

		HRESULT loadTexture(const char *fileName, DWORD transcolor, UINT &width, UINT &height, LPDIRECT3DTEXTURE9 &texture);
		HRESULT loadTextureIntoSystemMemory(const char *fileName, DWORD transcolor, UINT &width, UINT &height, LPDIRECT3DTEXTURE9 &texture);

		HRESULT loadMesh(const char* fileName);

		HRESULT beginScene();
		HRESULT endScene();
		HRESULT showBackBuffer();

		void beginSpriteDraw();
		void endSpriteDraw();

		void drawSprite(const SpriteData& spriteData, DWORD color);

		void drawMesh(const Mesh& mesh, class TransformComponent* transform);

		static D3DXMATRIX getWorldMatrix(class TransformComponent* transform);
		static D3DXMATRIX getViewMatrix(class CameraComponent* camera);
		static D3DXMATRIX getProjectionMatrix(class CameraComponent* camera);

		LPDIRECT3D9 getDirect3D(){return direct3D;}

		LPDIRECT3DDEVICE9 getDevice(){return device;}

		HDC getDeviceContext(){return GetDC(window);}

		HRESULT getDeviceState();

		LPD3DXSPRITE getSprite(){return sprite;}

		Mesh getMesh(const char* fileName){return meshes[fileName];}

		void setActiveCamera(class CameraComponent* camera){this->activeCamera = camera;}
};
