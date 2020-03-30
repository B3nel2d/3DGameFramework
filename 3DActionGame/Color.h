//======================================================================
//
//	Color
//
//	êFÇ…ä÷Ç∑ÇÈÉNÉâÉX
//
//======================================================================

#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "Math.h"

class Color{
	public:
		float r;
		float g;
		float b;
		float a;

		static Color black;
		static Color white;
		static Color red;
		static Color green;
		static Color blue;
		static Color yellow;
		static Color cyan;
		static Color magenta;

		Color(){
			Color(0.0f, 0.0f, 0.0f, 1.0f);
		}
		Color(float r, float g, float b, float a = 1.0f){
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}
		Color(int r, int g, int b, int a = 255){
			this->r = (float)(r / 255);
			this->g = (float)(g / 255);
			this->b = (float)(b / 255);
			this->a = (float)(a / 255);
		}

		DWORD toDWord(){
			return (DWORD)(((((int)(a * 255)) & 0xff) << 24) | ((((int)(r * 255)) & 0xff) << 16) | ((((int)(g * 255)) & 0xff) << 8) | (((int)(b * 255)) & 0xff));
		}
		static DWORD toDWord(Color color){
			return (DWORD)(((((int)(color.a * 255)) & 0xff) << 24) | ((((int)(color.r * 255)) & 0xff) << 16) | ((((int)(color.g * 255)) & 0xff) << 8) | (((int)(color.b * 255)) & 0xff));
		}

	private:
		friend Color operator +(const Color& left, const Color& right){
			Color result = Color(left.r + right.r, left.g + right.g, left.b + right.b);

			Math::clamp(result.r, 0.0f, 1.0f);
			Math::clamp(result.g, 0.0f, 1.0f);
			Math::clamp(result.b, 0.0f, 1.0f);

			return result;
		}

		friend Color operator *(const Color& left, const Color& right){
			Color result = Color(left.r * right.r, left.g * right.g, left.b * right.b);

			Math::clamp(result.r, 0.0f, 1.0f);
			Math::clamp(result.g, 0.0f, 1.0f);
			Math::clamp(result.b, 0.0f, 1.0f);

			return result;
		}

		friend Color operator *(const Color& color, float scalar){
			Color result = Color(color.r * scalar, color.g * scalar, color.b * scalar);

			Math::clamp(result.r, 0.0f, 1.0f);
			Math::clamp(result.g, 0.0f, 1.0f);
			Math::clamp(result.b, 0.0f, 1.0f);

			return result;
		}

		friend Color operator *(float scalar, const Color& color){
			Color result = Color(color.r * scalar, color.g * scalar, color.b * scalar);

			Math::clamp(result.r, 0.0f, 1.0f);
			Math::clamp(result.g, 0.0f, 1.0f);
			Math::clamp(result.b, 0.0f, 1.0f);

			return result;
		}

		friend bool operator ==(const Color& left, const Color& right){
			return left.r == right.r && left.g == right.g && left.b == right.b;
		}

		Color& operator *=(float scalar){
			r *= scalar;
			g *= scalar;
			b *= scalar;

			Math::clamp(r, 0.0f, 1.0f);
			Math::clamp(g, 0.0f, 1.0f);
			Math::clamp(b, 0.0f, 1.0f);

			return *this;
		}

		Color& operator +=(const Color& right){
			r += right.r;
			g += right.g;
			b += right.b;

			Math::clamp(r, 0.0f, 1.0f);
			Math::clamp(g, 0.0f, 1.0f);
			Math::clamp(b, 0.0f, 1.0f);

			return *this;
		}
};
