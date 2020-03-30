#include "Input.h"

/**********************************************************************
	�R���X�g���N�^�[
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
	�f�R���X�g���N�^�[
**********************************************************************/
Input::~Input(){
    if(isMouseCaptured)
        ReleaseCapture();
}

/**********************************************************************
	initialize

	���������s��
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

	�w��L�[��������ԂƂ���
**********************************************************************/
void Input::setKeyDown(WPARAM keyCode){
    if(keyCode < KEY_ARRAY_LENGTH){
        downedKeys[keyCode] = true;
        pressedKeys[keyCode] = true;
    }
}

/**********************************************************************
	setKeyUp

	�w��L�[�������ԂƂ���
**********************************************************************/
void Input::setKeyUp(WPARAM keyCode){
	if(keyCode < KEY_ARRAY_LENGTH){
		downedKeys[keyCode] = false;
	}
}

/**********************************************************************
	setInputKey

	�w��L�[�ɉ����ē��͏���ۑ�����
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

	�w��L�[��������Ԃ����肷��
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

	�w��L�[���O�t���[���ŉ�����Ă��������肷��
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

	���炩�̃L�[���O�t���[���ŉ�����Ă��������肷��
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

	�O�t���[���̃L�[���������N���A����
**********************************************************************/
void Input::clearKeyPress(UCHAR virtualKey){
	if(virtualKey < KEY_ARRAY_LENGTH){
		pressedKeys[virtualKey] = false;
	}
}

/**********************************************************************
	clear

	���͏����N���A����
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

	���͏���S�ăN���A����
**********************************************************************/
void Input::clearAll(){
	clear(INPUTS);
}

/**********************************************************************
	clearInputText

	���͂��ꂽ�e�L�X�g���N���A����
**********************************************************************/
void Input::clearInputText(){
	inputText.clear();
}

/**********************************************************************
	clearInputCharacter

	���͂��ꂽ�������N���A����
**********************************************************************/
void Input::clearInputCharacter(){
	inputCharacter = 0;
}

/**********************************************************************
	inputMousePosition

	�}�E�X�̍��W����͂���
**********************************************************************/
void Input::inputMousePosition(LPARAM position){
    mousePositionX = GET_X_LPARAM(position); 
    mousePositionY = GET_Y_LPARAM(position);
}

/**********************************************************************
	inputMouseWheelPosition

	�}�E�X�z�C�[���̈ʒu����͂���
**********************************************************************/
void Input::inputMouseWheelPosition(WPARAM position){
    mouseWheelPosition = GET_WHEEL_DELTA_WPARAM(position);
}
