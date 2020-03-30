//======================================================================
//
//	Text
//
//	UIテキストのクラス
//
//======================================================================

#pragma once

#define WIN32_LEAN_AND_MEAN

#include <string>
#include "Image.h"
#include "Settings.h"

using namespace std;

class Text : public Image{
	private:
		LPD3DXFONT font;

		float rotationAngle;
		RECT rectangle;
		D3DXMATRIX matrix;
		Color color;

		Graphics *graphics;

	public:
		Text();
		virtual ~Text();

		virtual bool initialize(Graphics *graphics, const string &fontName, int height, bool bold, bool italic);

		virtual int print(const string &string, const Vector2D& position);
		virtual int print(const string &string, RECT &rectangle, UINT format);

		virtual void onLostDevice();
		virtual void onResetDevice();

		virtual void setTextRectangle(const RECT& rectangle){this->rectangle = rectangle;}

		virtual float getRotationAngle(){return rotationAngle;}
		virtual void setRotationAngle(float angle){this->rotationAngle = angle;}

		virtual Color getColor(){return color;}
		virtual void setColor(const Color& color){this->color = color;}
};
