#include "Game.h"
#include "MainLevel.h"

Game* Game::instance = nullptr;

/**********************************************************************
	コンストラクター
**********************************************************************/
Game::Game(){
    input = new Input();
	graphics = NULL;
	audio = NULL;

	initialized = false;
    paused = false;
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
Game::~Game(){
    deleteResources();
    ShowCursor(true);
}

/**********************************************************************
	createInstance

	インスタンスの生成を行う
**********************************************************************/
void Game::createInstance(){
	if(!instance){
		instance = new Game();
	}
}

/**********************************************************************
	destroyInstance

	インスタンスの削除を行う
**********************************************************************/
void Game::destroyInstance(){
	if(instance){
		delete instance;
		instance = nullptr;
	}
}

/**********************************************************************
	getInstance

	インスタンスを取得する
**********************************************************************/
Game* Game::getInstance(){
	return instance;
}

/**********************************************************************
	initialize

	ゲームの初期化を行う
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

	ゲームに使用する全てのレベルを初期化し管理下に置く
**********************************************************************/
void Game::initializeLevels(){
	levels["Main Level"] = new MainLevel();
	levels["Main Level"]->initialize();

	currentLevel = levels["Main Level"];
}

/**********************************************************************
	run

	ゲームループ内の毎フレームで実行する処理を行う
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

	ゲームを停止する
**********************************************************************/
void Game::shutdown(){
	PostMessage(window, WM_DESTROY, 0, 0);
}

/**********************************************************************
	deleteResources

	管理下にある全リソースの解放を行う
**********************************************************************/
void Game::deleteResources(){
	deleteResource(graphics);
    deleteResource(input);

	levels.clear();

    initialized = false;
}

/**********************************************************************
	messageHandler

	メッセージに応じて規定された処理を行う
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
