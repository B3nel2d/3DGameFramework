#include "Mesh.h"
#include "Settings.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
Mesh::Mesh(){
	mesh = NULL;

	materials = NULL;
	materialCount = 0;

	textures = NULL;
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
Mesh::~Mesh(){

}

/**********************************************************************
	deleteResources

	全リソースの削除を行う
**********************************************************************/
void Mesh::deleteResources(){
	delete [] materials;
	materials = NULL;

	for(DWORD i = 0; i < materialCount; i++){
		if(!textures[i]){
			textures[i]->Release();
			textures[i]	= NULL;		
		}
	}

	delete [] textures;
	textures = NULL;
}
