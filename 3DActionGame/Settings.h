//======================================================================
//
//	Settings
//
//	ゲームの各設定を管理するクラス
//
//======================================================================

#pragma once

#define WIN32_LEAN_AND_MEAN

#include "Color.h"

const char CLASS_NAME[] = "3DActionGame";
const char GAME_TITLE[] = "3D Action Game";
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int UNIT = 100;
const bool IS_FULLSCREEN = false;

const float FRAME_RATE  = 200.0f;
const float MIN_FRAME_RATE = 10.0f;
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE;

const UCHAR ESC_KEY = VK_ESCAPE;
const UCHAR LEFT_KEY = VK_LEFT;
const UCHAR RIGHT_KEY = VK_RIGHT;
const UCHAR UP_KEY = VK_UP;
const UCHAR DOWN_KEY = VK_DOWN;

const DWORD TRANSPARENT_COLOR = Color::magenta.toDWord();

const char NEBULA_IMAGE[] = "assets\\images\\nebula.jpg";
const char PLANET_IMAGE[] = "assets\\images\\planet.png";

const char WAVE_BANK[]  = "assets\\audios\\windows\\WavesExample1.xwb";
const char SOUND_BANK[] = "assets\\audios\\windows\\SoundsExample1.xsb";

const char BEEP1[] = "beep1";
const char BEEP2[] = "beep2";
const char BEEP3[] = "beep3";
const char BEEP4[] = "beep4";
const char HIT[]   = "hit";

template <typename Type>
inline void releaseResource(Type& pointer){
    if(pointer){ 
        pointer->Release(); 
        pointer = NULL;
    }
}

template <typename Type>
inline void deleteResource(Type& pointer){
    if(pointer){ 
        delete pointer; 
        pointer = NULL;
    }
}

template <typename Type>
inline void deleteArrayResource(Type& pointer){
    if(pointer){ 
        delete[] pointer; 
        pointer = NULL;
    }
}
