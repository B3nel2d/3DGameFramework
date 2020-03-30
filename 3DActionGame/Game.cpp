#include "Game.h"
#include "MainLevel.h"

Game* Game::instance = nullptr;

/**********************************************************************
	�R���X�g���N�^�[
**********************************************************************/
Game::Game(){
    input = new Input();
	graphics = NULL;
	audio = NULL;

	initialized = false;
    paused = false;
}

/**********************************************************************
	�f�R���X�g���N�^�[
**********************************************************************/
Game::~Game(){
    deleteResources();
    ShowCursor(true);
}

/**********************************************************************
	createInstance

	�C���X�^���X�̐������s��
**********************************************************************/
void Game::createInstance(){
	if(!instance){
		instance = new Game();
	}
}

/**********************************************************************
	destroyInstance

	�C���X�^���X�̍폜���s��
**********************************************************************/
void Game::destroyInstance(){
	if(instance){
		delete instance;
		instance = nullptr;
	}
}

/**********************************************************************
	getInstance

	�C���X�^���X���擾����
**********************************************************************/
Game* Game::getInstance(){
	return instance;
}

/**********************************************************************
	initialize

	�Q�[���̏��������s��
**********************************************************************/
void Game::initialize(HWND window){
    this->window = window;

	input->initialize(window, false);

    graphics = new Graphics();
    graphics->initialize(window, WINDOW_WIDTH, WINDOW_HEIGHT, IS_FULLSCREEN);
	
    audio = new Audio();
    if(*WAVE_BANK != '\0' && *SOUND_BANK != '\0'){
        if(FAILED(result = audio->initialize())){
            if(result == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)){
                OutputDebugString("FATAL ERROR: Failed to initialize sound system because media file not found.\n");
			}
            else{
				OutputDebugString("FATAL ERROR: Failed to initialize sound system.\n");
			}
        }
    }
	
	if(QueryPerformanceFrequency(&timerFrequency) == false){
		OutputDebugString("FATAL ERROR: Failed to initialize high resolution timer.\n");
	}
    QueryPerformanceCounter(&startTime);

	initializeLevels();

    initialized = true;
}

/**********************************************************************
	initializeLevels

	�Q�[���Ɏg�p����S�Ẵ��x�������������Ǘ����ɒu��
**********************************************************************/
void Game::initializeLevels(){
	levels["Main Level"] = new MainLevel();
	levels["Main Level"]->initialize();

	currentLevel = levels["Main Level"];
}

/**********************************************************************
	run

	�Q�[�����[�v���̖��t���[���Ŏ��s���鏈�����s��
**********************************************************************/
void Game::run(HWND window){
	if(graphics == NULL){
		return;
	}

    QueryPerformanceCounter(&endTime);
    frameDeltaTime = (float)(endTime.QuadPart - startTime.QuadPart) / (float)timerFrequency.QuadPart;

    if(frameDeltaTime < MIN_FRAME_TIME){
        sleepTime = (DWORD)((MIN_FRAME_TIME - frameDeltaTime) * 1000);
        timeBeginPeriod(1);
        Sleep(sleepTime);
        timeEndPeriod(1);

        return;
    }

	if(0.0f < frameDeltaTime){
		framePerSecond = (framePerSecond * 0.99f) + (0.01f / frameDeltaTime);
	}
	if(frameDeltaTime > MAX_FRAME_TIME){
		frameDeltaTime = MAX_FRAME_TIME;
	}
        
    startTime = endTime;

    if(!paused){
        currentLevel->update();
        currentLevel->detectCollisions();
    }

    currentLevel->render();

    input->clear(PRESSED_KEYS);
}

/**********************************************************************
	shutdown

	�Q�[�����~����
**********************************************************************/
void Game::shutdown(){
	PostMessage(window, WM_DESTROY, 0, 0);
}

/**********************************************************************
	deleteResources

	�Ǘ����ɂ���S���\�[�X�̉�����s��
**********************************************************************/
void Game::deleteResources(){
	deleteResource(graphics);
    deleteResource(input);

	levels.clear();

    initialized = false;
}

/**********************************************************************
	messageHandler

	���b�Z�[�W�ɉ����ċK�肳�ꂽ�������s��
**********************************************************************/
LRESULT Game::messageHandler(HWND window, UINT message, WPARAM wParameter, LPARAM lParameter){
    if(initialized){
        switch(message){
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
            case WM_KEYDOWN: case WM_SYSKEYDOWN:
                input->setKeyDown(wParameter);
                return 0;
            case WM_KEYUP: case WM_SYSKEYUP:
                input->setKeyUp(wParameter);
                return 0;
            case WM_CHAR:
                input->setInputKey(wParameter);
                return 0;
            case WM_MOUSEMOVE:
                input->inputMousePosition(lParameter);
                return 0;
            case WM_LBUTTONDOWN:
                input->setMouseLeftButtonState(true);
                input->inputMousePosition(lParameter);
                return 0;
            case WM_LBUTTONUP:
                input->setMouseLeftButtonState(false);
                input->inputMousePosition(lParameter);
                return 0;
            case WM_MBUTTONDOWN:
                input->setMouseMiddleButtonState(true);
                input->inputMousePosition(lParameter);
                return 0;
            case WM_MBUTTONUP:
                input->setMouseMiddleButtonState(false);
                input->inputMousePosition(lParameter);
                return 0;
            case WM_RBUTTONDOWN:
                input->setMouseMiddleButtonState(true);
                input->inputMousePosition(lParameter);
                return 0;
            case WM_RBUTTONUP:
                input->setMouseRightButtonState(false);
                input->inputMousePosition(lParameter);
                return 0;
            case WM_XBUTTONDOWN: case WM_XBUTTONUP:
                input->setMouseRightButtonState(wParameter);
                input->inputMousePosition(lParameter);
                return 0;
            case WM_MOUSEWHEEL:
                input->inputMouseWheelPosition(wParameter);
                return 0;
        }
    }

    return DefWindowProc(window, message, wParameter, lParameter);
}
