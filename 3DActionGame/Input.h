//======================================================================
//
//	Input
//
//	キーやマウスなどの入力を管理するクラス
//
//======================================================================

#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <WindowsX.h>
#include <string>
#include <XInput.h>
#include "Settings.h"
#include "GameError.h"

const int KEY_ARRAY_LENGTH = 256;

const UCHAR DOWNED_KEYS = 1;
const UCHAR PRESSED_KEYS = 2;
const UCHAR MOUSE = 4;
const UCHAR TEXT = 8;
const UCHAR INPUTS = DOWNED_KEYS + PRESSED_KEYS + MOUSE + TEXT;

class Input{
	private:
		bool downedKeys[KEY_ARRAY_LENGTH];
		bool pressedKeys[KEY_ARRAY_LENGTH];

		std::string inputText;
		char inputCharacter;
		bool isNewLine;

		int mousePositionX;
		int mousePositionY;
		int mouseWheelPosition;

		bool isMouseCaptured;
		bool isMouseLeftButtonDown;
		bool isMouseMiddleButtonDown;
		bool isMouseRightButtonDown;

	public:
		Input();
		virtual ~Input();

		void initialize(HWND window, bool isCaptured);

		void setKeyDown(WPARAM keyCode);
		void setKeyUp(WPARAM keyCode);
		void setInputKey(WPARAM keyCode);

		bool isKeyDown(UCHAR virtualKey) const;
		bool wasKeyPressed(UCHAR virtualKey) const;
		bool wasAnyKeyPressed() const;

		void clearKeyPress(UCHAR virtualKey);
		void clear(UCHAR virtualKey);
		void clearAll();
		void clearInputText();
		void clearInputCharacter();

		std::string getInputText(){return inputText;}
		void setInputText(std::string text){inputText = text;}

		char getInputCharacter(){return inputCharacter;}

		void inputMousePosition(LPARAM position);
		void inputMouseWheelPosition(WPARAM position);

		void setMouseLeftButtonState(bool isDown){isMouseLeftButtonDown = isDown;}
		void setMouseMiddleButtonState(bool isDown){isMouseMiddleButtonDown = isDown;}
		void setMouseRightButtonState(bool isDown){isMouseRightButtonDown = isDown;}

		int getMousePositionX() const {return mousePositionX;}
		int getMousePositionY() const {return mousePositionY;}

		int getMouseWheelMovement(){ 
			int value = mouseWheelPosition;
			mouseWheelPosition = 0;
			return value; 
		}

		bool getMouseLeftButtonState() const {return isMouseLeftButtonDown;}
		bool getMouseMiddleButtonState() const {return isMouseLeftButtonDown;}
		bool getMouseRightButtonState() const {return isMouseLeftButtonDown;}
};
