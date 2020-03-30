#include "Text.h"

/**********************************************************************
	コンストラクター
**********************************************************************/
Text::Text(){
	font = NULL;

    rectangle.top = 0;
    rectangle.left = 0;
    rectangle.right = WINDOW_WIDTH;
    rectangle.bottom = WINDOW_HEIGHT;
    
    rotationAngle = 0;

	color = Color::white;
}

/**********************************************************************
	デコンストラクター
**********************************************************************/
Text::~Text(){
	releaseResource(font);
}

/**********************************************************************
	initialize

	初期化を行う
**********************************************************************/
bool Text::initialize(Graphics *graphics, const string &fontName, int height, bool bold, bool italic){
    this->graphics = graphics;

    UINT weight = FW_NORMAL;
    if(bold){
		weight = FW_BOLD;
	}

    if(FAILED(D3DXCreateFont(graphics->getDevice(), height, 0, weight, 1, italic, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, fontName.c_str(), &font))){
		return false;
	}

    D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, NULL, 0.0f, NULL);

    return true;
}

/**********************************************************************
	print

	描画を行う
**********************************************************************/
int Text::print(const string &string, const Vector2D& position){
    if(font == NULL){
		return 0;
	}

    rectangle.top = (LONG)position.y;
    rectangle.left = (LONG)position.x;

    D3DXVECTOR2 rotationCenter = D3DXVECTOR2(position.x, position.y);
    D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, &rotationCenter, rotationAngle, NULL);
    graphics->getSprite()->SetTransform(&matrix);

    return font->DrawTextA(graphics->getSprite(), string.c_str(), -1, &rectangle, DT_LEFT, color.toDWord());
}
int Text::print(const string &string, RECT &rectangle, UINT format){
    if(font == NULL){
		return 0;
	}

    D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, NULL, NULL, NULL);
    graphics->getSprite()->SetTransform(&matrix);

    return font->DrawTextA(graphics->getSprite(), string.c_str(), -1, &rectangle, format, color.toDWord());
}

/**********************************************************************
	onLostDevice

	グラフィックデバイス消失時の対応を行う
**********************************************************************/
void Text::onLostDevice(){
	if(font == NULL){
		return;
	}

    font->OnLostDevice();
}

/**********************************************************************
	onResetDevice

	グラフィックデバイスリセット時の対応を行う
**********************************************************************/
void Text::onResetDevice(){
    if(font == NULL){
		return;
	}

    font->OnResetDevice();
}
