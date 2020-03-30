//======================================================================
//
//	Texture
//
//	テクスチャークラス
//
//======================================================================

#pragma once

#define WIN32_LEAN_AND_MEAN

#include "Graphics.h"
#include "Settings.h"

class Texture{
	private:
		LPDIRECT3DTEXTURE9 textureData;
		const char* fileName;

		UINT width;
		UINT height;
		
		bool initialized;

		Graphics* graphics;

		HRESULT result;

	public:
		Texture();
		virtual ~Texture();

		virtual bool initialize(Graphics* graphics, const char* fileName);
		virtual void onLostDevice();
		virtual void onResetDevice();

		LPDIRECT3DTEXTURE9 getTextureData() const {return textureData;}

		UINT getWidth() const {return width;}
		UINT getHeight() const {return height;}
};
