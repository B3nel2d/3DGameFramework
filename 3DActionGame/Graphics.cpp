#include "Graphics.h"
#include "Color.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "CameraActor.h"

/**********************************************************************
	�R���X�g���N�^�[
**********************************************************************/
Graphics::Graphics(){
    direct3D = NULL;
    device = NULL;

    width = WINDOW_WIDTH;
    height = WINDOW_HEIGHT;
	backGroundColor = Color::blue.toDWord();
	fullScreen = IS_FULLSCREEN;

	activeCamera = nullptr;
}

/**********************************************************************
	�f�R���X�g���N�^�[
**********************************************************************/
Graphics::~Graphics(){
	release();
}

/**********************************************************************
	initialize

	�e�\���̂̏������␔�l�̐ݒ���s��
**********************************************************************/
void Graphics::initialize(HWND window, int width, int height, bool fullScreen){
	this->window = window;
    this->width = width;
    this->height = height;
    this->fullScreen = fullScreen;

    direct3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(direct3D == NULL){
		OutputDebugString("FATAL ERROR: Failed to initialize Direct3D.\n");
	}

    initializePresentationParameters();
	//direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode);

    if(fullScreen){
		if(isAdapterCompatible()){
			presentationParameters.FullScreen_RefreshRateInHz = displayMode.RefreshRate;
		}
		else{
			OutputDebugString("FATAL ERROR: The graphics device does not support the specified resolution and/or format.\n");
		}
    }

    D3DCAPS9 caps;
    DWORD behavior;

    result = direct3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	if((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 || caps.VertexShaderVersion < D3DVS_VERSION(1,1)){
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	else{
		behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}

    result = direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window, behavior, &presentationParameters, &device);
	if(FAILED(result)){
		OutputDebugString("FATAL ERROR: Failed to create Direct3D device.\n");
	}

	result = D3DXCreateSprite(device, &sprite);
	if(FAILED(result)){
		OutputDebugString("FATAL ERROR: Failed to create Direct3D sprite.");
	}
}

/**********************************************************************
	initializePresentationParameters

	�v���[���e�[�V�����p�����[�^�̐ݒ���s��
**********************************************************************/
void Graphics::initializePresentationParameters(){
    try{
        ZeroMemory(&presentationParameters, sizeof(presentationParameters));

        presentationParameters.BackBufferWidth = width;
        presentationParameters.BackBufferHeight = height;

		if(fullScreen){
			presentationParameters.BackBufferFormat = D3DFMT_X8R8G8B8;
		}
		else{
			presentationParameters.BackBufferFormat = D3DFMT_UNKNOWN;
		}

        presentationParameters.BackBufferCount = 1;
        presentationParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
        presentationParameters.hDeviceWindow = window;
        presentationParameters.Windowed = (!fullScreen);
        presentationParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    }
	catch(...){
		OutputDebugString("FATAL ERROR: Failed to initialize Direct3D presentation parameters.\n");
    }
}

/**********************************************************************
	release

	�e���\�[�X�̉�����s��
**********************************************************************/
void Graphics::release(){
    releaseResource(device);
    releaseResource(direct3D);
	releaseResource(sprite);
	unordered_map<string, Mesh>().swap(meshes);
}

/**********************************************************************
	isAdapterCompatible

	�f�B�X�v���C�A�_�v�^�[�̓K�������m�F����
**********************************************************************/
bool Graphics::isAdapterCompatible(){
    UINT modes = direct3D->GetAdapterModeCount(D3DADAPTER_DEFAULT, presentationParameters.BackBufferFormat);
    for(UINT i = 0; i < modes; i++){
        result = direct3D->EnumAdapterModes( D3DADAPTER_DEFAULT, presentationParameters.BackBufferFormat, i, &displayMode);
		if(displayMode.Height == presentationParameters.BackBufferHeight && displayMode.Width == presentationParameters.BackBufferWidth && presentationParameters.FullScreen_RefreshRateInHz <= displayMode.RefreshRate){
			return true;
		}
    }

    return false;
}

/**********************************************************************
	reset

	�O���t�B�b�N�f�o�C�X�̃��Z�b�g���s��
**********************************************************************/
HRESULT Graphics::reset(){
    initializePresentationParameters();
    result = device->Reset(&presentationParameters);

    return result;
}

/**********************************************************************
	loadTexture

	�w��t�@�C������e�N�X�`���[��ǂݍ���
**********************************************************************/
HRESULT Graphics::loadTexture(const char *fileName, DWORD transparentColor, UINT &width, UINT &height, LPDIRECT3DTEXTURE9 &texture){
    D3DXIMAGE_INFO imageInfomation;
    result = E_FAIL;

    try{
        if(fileName == NULL){
            texture = NULL;
            return D3DERR_INVALIDCALL;
        }
		if(meshes.count(fileName) != 0){
			return D3D_OK;
		}
    
        result = D3DXGetImageInfoFromFile(fileName, &imageInfomation);
		if(result != D3D_OK){
			return result;
		}
            
        width = imageInfomation.Width;
        height = imageInfomation.Height;
    
        result = D3DXCreateTextureFromFileEx(device, fileName, imageInfomation.Width, imageInfomation.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, transparentColor, &imageInfomation, NULL, &texture);
    }
	catch(...){
        OutputDebugString("ERROR: Failed to load texture.");
    }

    return result;
}

/**********************************************************************
	loadTextureIntoSystemMemory

	�V�X�e���������[�Ƀe�N�X�`���[��ǂݍ���
**********************************************************************/
HRESULT Graphics::loadTextureIntoSystemMemory(const char *fileName, DWORD transparentColor, UINT &width, UINT &height, LPDIRECT3DTEXTURE9 &texture){
    D3DXIMAGE_INFO imageInformation;
    result = E_FAIL;

    try{
        if(fileName == NULL){
            texture = NULL;
            return D3DERR_INVALIDCALL;
        }

        result = D3DXGetImageInfoFromFile(fileName, &imageInformation);

        if(result != D3D_OK){
            return result;
		}

        width = imageInformation.Width;
        height = imageInformation.Height;

        result = D3DXCreateTextureFromFileEx( 
            device,
            fileName,
            imageInformation.Width,
            imageInformation.Height,
            1,
            0,
            D3DFMT_UNKNOWN,
            D3DPOOL_SYSTEMMEM,
            D3DX_DEFAULT,
            D3DX_DEFAULT,
            transparentColor,
            &imageInformation,
            NULL,
            &texture
		);

    }
	catch(...){
		OutputDebugString("ERROR: Failed to load texture.\n");
    }

    return result;
}

/**********************************************************************
	loadMesh

	�w��t�@�C�����烁�b�V����ǂݍ���
**********************************************************************/
HRESULT Graphics::loadMesh(const char* fileName){
	Mesh mesh;
	LPD3DXBUFFER materialBuffer = NULL;
    result = E_FAIL;

    try{
        if(fileName == NULL){
			OutputDebugString("ERROR: Invalid file name.\n");
            return D3DERR_INVALIDCALL;
        }
    
        result = D3DXLoadMeshFromX(fileName, D3DXMESH_SYSTEMMEM, device, nullptr, &materialBuffer, NULL, &(mesh.materialCount), &(mesh.mesh));
		if(FAILED(result)){
			OutputDebugString("ERROR: Failed to load mesh.\n");
			return result;
		}

		D3DXMATERIAL* materials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();
		mesh.materials = new D3DMATERIAL9[mesh.materialCount];
		mesh.textures = new LPDIRECT3DTEXTURE9[mesh.materialCount];

		for(DWORD i = 0; i < mesh.materialCount; i++){
			mesh.materials[i] = materials[i].MatD3D;  
			mesh.materials[i].Ambient = mesh.materials[i].Diffuse;
			mesh.textures[i] = NULL;

			if(materials[i].pTextureFilename != NULL && 0 < lstrlen(materials[i].pTextureFilename)){      
				if(FAILED(D3DXCreateTextureFromFile(device, materials[i].pTextureFilename, &mesh.textures[i]))){     
					OutputDebugString("ERROR: Failed to load a texture of mesh.\n");
				}
			}
		}

		materialBuffer->Release();

		meshes[fileName] = mesh;
    }
	catch(...){
        OutputDebugString("ERROR: Failed to load mesh.");
    }

    return result;
}

/**********************************************************************
	beginScene

	�t�����g�o�b�t�@���N���A���`����J�n����
**********************************************************************/
HRESULT Graphics::beginScene(){
    result = E_FAIL;
	if(device == NULL){
		return result;
	}

    device->Clear(0, NULL, D3DCLEAR_TARGET, backGroundColor, 1.0F, 0);
    result = device->BeginScene();

    return result;
}

/**********************************************************************
	endScene

	�`����I������
**********************************************************************/
HRESULT Graphics::endScene(){
    result = E_FAIL;
	if(device){
		result = device->EndScene();
	}

    return result;
}

/**********************************************************************
	showBackBuffer

	�t�����g�o�b�t�@�ƃo�b�N�o�b�t�@����������
**********************************************************************/
HRESULT Graphics::showBackBuffer(){
    result = device->Present(NULL, NULL, NULL, NULL);

    return result;
}

/**********************************************************************
	beginSpriteDraw

	�X�v���C�g�̕`����J�n����
**********************************************************************/
void Graphics::beginSpriteDraw() {
    sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

/**********************************************************************
	endSpriteDraw

	�X�v���C�g�̕`����I������
**********************************************************************/
void Graphics::endSpriteDraw(){
    sprite->End();
}

/**********************************************************************
	drawSprite

	�w��X�v���C�g�̕`����s��
**********************************************************************/
void Graphics::drawSprite(const SpriteData &spriteData, DWORD color){
    if(spriteData.texture == NULL){
        return;
	}

    D3DXVECTOR2 spriteCenter = D3DXVECTOR2((float)(spriteData.size.x / 2.0f * spriteData.scale.x), (float)(spriteData.size.y / 2.0f * spriteData.scale.y));
    D3DXVECTOR2 translate = D3DXVECTOR2((float)spriteData.position.x, (float)spriteData.position.y);
    D3DXVECTOR2 scaling(spriteData.scale.x, spriteData.scale.y);

    if(spriteData.horizontalFlip){
        scaling.x *= -1;
        spriteCenter.x -= (float)(spriteData.size.x * spriteData.scale.x);
        translate.x += (float)(spriteData.size.x * spriteData.scale.x);
    }
    if(spriteData.verticalFlip){
        scaling.y *= -1;
        spriteCenter.y -= (float)(spriteData.size.y * spriteData.scale.y);
        translate.y += (float)(spriteData.size.y * spriteData.scale.y);
    }

    D3DXMATRIX matrix;
    D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, &scaling, &spriteCenter, (float)(spriteData.rotation), &translate);

    sprite->SetTransform(&matrix);
    sprite->Draw(spriteData.texture, &spriteData.rectangle, NULL, NULL, color);
}

/**********************************************************************
	drawMesh

	�w�胁�b�V���̕`����s��
**********************************************************************/
void Graphics::drawMesh(const Mesh& mesh, TransformComponent* transform){
	device->SetTransform(D3DTS_WORLD, &getWorldMatrix(transform));
	device->SetTransform(D3DTS_VIEW, &getViewMatrix(activeCamera));
	device->SetTransform(D3DTS_PROJECTION, &getProjectionMatrix(activeCamera));

	for(DWORD i = 0; i < mesh.materialCount; i++){
		device->SetMaterial(&mesh.materials[i]);
		device->SetTexture(0, mesh.textures[i]);
		mesh.mesh->DrawSubset(i);
	}
}

/**********************************************************************
	getWorldMatrix

	���[���h���W�ϊ��s����擾����
**********************************************************************/
D3DXMATRIX Graphics::getWorldMatrix(TransformComponent* transform){
	D3DXMATRIX scalingMatrix;
	D3DXMatrixIdentity(&scalingMatrix);
	D3DXMatrixScaling(&scalingMatrix, transform->getScale().x, transform->getScale().y, transform->getScale().z);

	D3DXMATRIX rotationMatrix;
	D3DXMatrixIdentity(&rotationMatrix);
	D3DXMatrixRotationQuaternion(&rotationMatrix, &(transform->getRotation().toD3DXQUATERNION()));

	D3DXMATRIX translationMatrix;
	D3DXMatrixIdentity(&translationMatrix);
	D3DXMatrixTranslation(&translationMatrix, transform->getPosition().x, transform->getPosition().y, transform->getPosition().z);

	D3DXMATRIX worldMatrix;
	D3DXMatrixIdentity(&worldMatrix);
	worldMatrix = scalingMatrix * rotationMatrix;
	worldMatrix = worldMatrix * translationMatrix;

	return worldMatrix;
}

/**********************************************************************
	getViewMatrix

	�r���[���W�ϊ��s����擾����
**********************************************************************/
D3DXMATRIX Graphics::getViewMatrix(CameraComponent* camera){
	D3DXMATRIX viewMatrix;

	D3DXMatrixIdentity(&viewMatrix);
	D3DXMatrixLookAtLH(&viewMatrix, &camera->getTransform()->getPosition().toD3DXVECTOR3(), &camera->getLookPosition().toD3DXVECTOR3(), &camera->getUpVector().toD3DXVECTOR3());

	return viewMatrix;
}

/**********************************************************************
	getProjectionMatrix

	�v���W�F�N�V�������W�ϊ��s����擾����
**********************************************************************/
D3DXMATRIX Graphics::getProjectionMatrix(CameraComponent* camera){
	D3DXMATRIX projectionMatrix;

	D3DXMatrixIdentity(&projectionMatrix);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, camera->getFieldOfView(), ((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT), camera->getNearClippingPlaneDistance(), camera->getFarClippingPlaneDistance());

	return projectionMatrix;
}

/**********************************************************************
	getDeviceState

	�O���t�B�b�N�f�o�C�X���������Ă��Ȃ����m�F����
**********************************************************************/
HRESULT Graphics::getDeviceState(){ 
    result = E_FAIL;
	if(device == NULL){
		return result;
	}

    result = device->TestCooperativeLevel();

    return result;
}
