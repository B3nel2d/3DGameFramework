//======================================================================
//
//	Mesh
//
//	3Dモデルのメッシュクラス
//
//======================================================================

#pragma once

#include <d3dx9.h>
#include <vector>

using namespace std;

class Mesh{
	public:
		LPD3DXMESH mesh;

		D3DMATERIAL9* materials;
		DWORD materialCount;

		LPDIRECT3DTEXTURE9* textures;

		Mesh();
		~Mesh();

		void deleteResources();
};
