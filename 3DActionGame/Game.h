//======================================================================
//
//	Game
//
//	ゲームとして最低限の機能である
//	初期化、ゲームループと終了処理に加え、
//	レベルの管理を行うシングルトンクラス
//
//======================================================================

#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <Mmsystem.h>
#include <unordered_map>
#include "Input.h"
#include "Graphics.h"
#include "Audio.h"
#include "Level.h"
#include "Settings.h"

using namespace std;

class Game{
	private:
		static Game* instance;

		HWND window;

		Input* input;
		Graphics* graphics;
		Audio* audio;

		unordered_map<string, Level*> levels;
		Level* currentLevel;

		LARGE_INTEGER startTime;
		LARGE_INTEGER endTime;
		LARGE_INTEGER timerFrequency;
		float frameDeltaTime;
		float framePerSecond;
		DWORD sleepTime;

		bool initialized;
		bool paused;

		HRESULT result;

		void initializeLevels();

	public:
		Game();
		virtual ~Game();

		static void createInstance();
		static void destroyInstance();
		static Game* getInstance();

		void initialize(HWND window);
		void run(HWND window);
		void shutdown();

		void deleteResources();

		LRESULT messageHandler(HWND window, UINT message, WPARAM wParameter, LPARAM lParameter);

		Input* getInput(){return input;}
		Graphics* getGraphics(){return graphics;}
		Audio* getAudio(){return audio;}

		Level* getCurrentLevel(){return currentLevel;}
		Level* getLevel(string levelName){return levels[levelName];}

		float getFrameDeltaTime(){return frameDeltaTime;}
		float getFramePerSecond(){return framePerSecond;}
};
