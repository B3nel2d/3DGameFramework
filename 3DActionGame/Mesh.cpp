#include "Mesh.h"
#include "Settings.h"

/**********************************************************************
	�R���X�g���N�^�[
**********************************************************************/
Mesh::Mesh(){
	mesh = NULL;

	materials = NULL;
	materialCount = 0;

	textures = NULL;
}

/**********************************************************************
	�f�R���X�g���N�^�[
**********************************************************************/
Mesh::~Mesh(){

}

/**********************************************************************
	deleteResources

	�S���\�[�X�̍폜���s��
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
