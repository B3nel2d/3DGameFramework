//======================================================================
//
//	WinMain
//
//	メインクラス
//
//======================================================================

#pragma once

#define WIN32_LEAN_AND_MEAN
#define _CRTDBG_MAP_ALLOC

#include <windows.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "d3d9.h"
#include "Game.h"
#include "Settings.h"

HWND window;
Game* game;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, PSTR commandLine, int commandShow);
bool CreateGameWindow(HWND window, HINSTANCE instance, int commandShow);
LRESULT WINAPI WindowProcedure(HWND window, UINT message, WPARAM wParameter, LPARAM lParameter);

/**********************************************************************
	WinMain

	本アプリケーションの開始点
**********************************************************************/
int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, PSTR commandLine, int commandShow){
	Game::createInstance();
	game = Game::getInstance();

	WNDCLASS windowClass;
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc	= WindowProcedure;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = instance;
	windowClass.hIcon = LoadIcon(NULL , IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL , IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = CLASS_NAME;

	if(!RegisterClass(&windowClass)){
		OutputDebugString("FATAL ERROR: Failed to register window class.\n");
		return 1;
	}

	window = CreateWindow(CLASS_NAME, GAME_TITLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, instance, NULL);
	if(!window){
		OutputDebugString("FATAL ERROR: Failed to create window.\n");
		return 1;
	}

    if(!IS_FULLSCREEN){
        RECT clientRect;
        GetClientRect(window, &clientRect);

        MoveWindow(window, 0, 0, WINDOW_WIDTH + (WINDOW_WIDTH - clientRect.right), WINDOW_HEIGHT + (WINDOW_HEIGHT - clientRect.bottom), TRUE);
    }
	
	game->initialize(window);

	MSG message;
	bool done = false;
	while(!done){
		if(PeekMessage(&message, NULL, 0, 0, PM_REMOVE)){
			if(message.message == WM_QUIT){
				done = true;
			}

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else{
			game->run(window);
		}
	}

	Game::destroyInstance();

	return (int)message.wParam;
}

/**********************************************************************
	CreateGameWindow

	ウィンドウの設定と生成を行う
**********************************************************************/
bool CreateGameWindow(HWND window, HINSTANCE instance, int commandShow){
	WNDCLASS windowClass;

	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc	= WindowProcedure;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = instance;
	windowClass.hIcon = LoadIcon(NULL , IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL , IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = CLASS_NAME;

	if(!RegisterClass(&windowClass)){
		OutputDebugString("FATAL ERROR: Failed to register window class.\n");
		return false;
	}

	window = CreateWindow(CLASS_NAME, GAME_TITLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, instance, NULL);
	if(!window){
		OutputDebugString("FATAL ERROR: Failed to create window.\n");
		return false;
	}

    if(!IS_FULLSCREEN){
        RECT clientRect;
        GetClientRect(window, &clientRect);

        MoveWindow(window, 0, 0, WINDOW_WIDTH + (WINDOW_WIDTH - clientRect.right), WINDOW_HEIGHT + (WINDOW_HEIGHT - clientRect.bottom), TRUE);
    }

	return true;
}

/**********************************************************************
	WindowProcedure

	メッセージに応じて規定された処理を行う
**********************************************************************/
LRESULT WINAPI WindowProcedure(HWND window, UINT message, WPARAM wParameter, LPARAM lParameter){
	return game->messageHandler(window, message, wParameter, lParameter);

	switch(message){
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(window, message, wParameter, lParameter);
}
