#include "Input.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
Input::Input(){
	for(size_t i = 0; i < KEY_ARRAY_LENGTH; i++){
		downedKeys[i] = false;
	}
    for(size_t i = 0; i < KEY_ARRAY_LENGTH; i++){
		pressedKeys[i] = false;
	}
        
    isNewLine = true;
    inputText = "";
    inputCharacter = 0;

    mousePositionX = 0;
    mousePositionY = 0;
    mouseWheelPosition = 0;
    isMouseLeftButtonDown = false;
    isMouseMiddleButtonDown = false;
    isMouseRightButtonDown = false;
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
Input::~Input(){
    if(isMouseCaptured)
        ReleaseCapture();
}

/**********************************************************************
	initialize

	初期化を行う
**********************************************************************/
void Input::initialize(HWND window, bool isCaptured){
    try{
        isMouseCaptured = isCaptured;

		if(isMouseCaptured){
			SetCapture(window);
		}
    }
    catch(...){
		OutputDebugString("FATAL ERROR: Failed to initialize input system.\n");
    }
}

/**********************************************************************
	setKeyDown

	指定キーを押下状態とする
**********************************************************************/
void Input::setKeyDown(WPARAM keyCode){
    if(keyCode < KEY_ARRAY_LENGTH){
        downedKeys[keyCode] = true;
        pressedKeys[keyCode] = true;
    }
}

/**********************************************************************
	setKeyUp

	指定キーを解放状態とする
**********************************************************************/
void Input::setKeyUp(WPARAM keyCode){
	if(keyCode < KEY_ARRAY_LENGTH){
		downedKeys[keyCode] = false;
	}
}

/**********************************************************************
	setInputKey

	指定キーに応じて入力情報を保存する
**********************************************************************/
void Input::setInputKey(WPARAM keyCode){
    if(isNewLine){
        inputText.clear();
        isNewLine = false;
    }

    if(keyCode == '\b'){
		if(inputText.length() > 0){
			inputText.erase(inputText.size()-1);
		}
    }
    else{
        inputText += keyCode;
        inputCharacter = keyCode;
    }

	if((char)keyCode == '\r'){
		isNewLine = true;
	}
}

/**********************************************************************
	isKeyDown

	指定キーが押下状態か判定する
**********************************************************************/
bool Input::isKeyDown(UCHAR virtualKey) const{
	if(virtualKey < KEY_ARRAY_LENGTH){
		return downedKeys[virtualKey];
	}
	else{
		return false;
	}
}

/**********************************************************************
	wasKeyPressed

	指定キーが前フレームで押されていたか判定する
**********************************************************************/
bool Input::wasKeyPressed(UCHAR virtualKey) const{
	if(virtualKey < KEY_ARRAY_LENGTH){
		return pressedKeys[virtualKey];
	}
	else{
		return false;
	}
}

/**********************************************************************
	wasAnyKeyPressed

	何らかのキーが前フレームで押されていたか判定する
**********************************************************************/
bool Input::wasAnyKeyPressed() const{
	for(size_t i = 0; i < KEY_ARRAY_LENGTH; i++){
		if(pressedKeys[i] == true){
			return true;
		}
	}

	return false;
}

/**********************************************************************
	clearKeyPress

	前フレームのキー押下情報をクリアする
**********************************************************************/
void Input::clearKeyPress(UCHAR virtualKey){
	if(virtualKey < KEY_ARRAY_LENGTH){
		pressedKeys[virtualKey] = false;
	}
}

/**********************************************************************
	clear

	入力情報をクリアする
**********************************************************************/
void Input::clear(UCHAR virtualKey){
    if(virtualKey & DOWNED_KEYS){
		for(size_t i = 0; i < KEY_ARRAY_LENGTH; i++){
			downedKeys[i] = false;
		}
    }
    if(virtualKey & PRESSED_KEYS){
		for(size_t i = 0; i < KEY_ARRAY_LENGTH; i++){
			pressedKeys[i] = false;
		}
    }
    if(virtualKey & MOUSE){
        mousePositionX = 0;
        mousePositionY = 0;
        mouseWheelPosition = 0;
    }
    if(virtualKey & TEXT){
        clearInputText();
        clearInputCharacter();
    }
}

/**********************************************************************
	clearAll

	入力情報を全てクリアする
**********************************************************************/
void Input::clearAll(){
	clear(INPUTS);
}

/**********************************************************************
	clearInputText

	入力されたテキストをクリアする
**********************************************************************/
void Input::clearInputText(){
	inputText.clear();
}

/**********************************************************************
	clearInputCharacter

	入力された文字をクリアする
**********************************************************************/
void Input::clearInputCharacter(){
	inputCharacter = 0;
}

/**********************************************************************
	inputMousePosition

	マウスの座標を入力する
**********************************************************************/
void Input::inputMousePosition(LPARAM position){
    mousePositionX = GET_X_LPARAM(position); 
    mousePositionY = GET_Y_LPARAM(position);
}

/**********************************************************************
	inputMouseWheelPosition

	マウスホイールの位置を入力する
**********************************************************************/
void Input::inputMouseWheelPosition(WPARAM position){
    mouseWheelPosition = GET_WHEEL_DELTA_WPARAM(position);
}
