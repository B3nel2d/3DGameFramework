//======================================================================
//
//	Math
//
//	ベクトルや四元数など数学関連の処理をまとめたクラス
//
//======================================================================

#pragma once
#include <limits>
#include <cmath>
#include <string>
#include <d3dx9.h>

using namespace std;

namespace Math{
	const float pi = 3.1415926535f;
	const float positiveInfinity = std::numeric_limits<float>::infinity();
	const float negativeInfinity = -std::numeric_limits<float>::infinity();
	const float epsilon = 0.001f;

	inline float getAbsolute(float value){
		return fabs(value);
	}

	inline float getPower(float base, float exponent){
		return powf(base, exponent);
	}

	inline float getSquareRoot(float value){
		return sqrtf(value);
	}

	inline float getLog(float value){
		return log(value);
	}

	template <typename Type>
	Type getMaximum(const Type& a, const Type& b){
		return (a < b ? b : a);
	}

	template <typename Type>
	Type getMinimum(const Type& a, const Type& b){
		return (a < b ? a : b);
	}

	template <typename Type>
	Type clamp(const Type& value, const Type& lower, const Type& upper){
		return getMinimum(upper, getMaximum(lower, value));
	}

	inline float lerp(float a, float b, float f){
		return a + f * (b - a);
	}

	inline float getCosine(float angle){
		return cosf(angle);
	}

	inline float getSine(float angle){
		return sinf(angle);
	}

	inline float getTangent(float angle){
		return tanf(angle);
	}

	inline float getArcSine(float value){
		return asinf(value);
	}

	inline float getArcCosine(float value){
		return acosf(value);
	}
	
	inline float getArcTangent(float y, float x){
		return atan2f(y, x);
	}

	inline float getCotangent(float angle){
		return 1.0f / tanf(angle);
	}

	inline float toRadian(float degrees){
		return degrees * pi / 180.0f;
	}

	inline float toDegrees(float radians){
		return radians * 180.0f / pi;
	}

	inline bool areApproximate(float a, float b){
		if(fabs(a - b) <= epsilon){
			return true;
		}

		return false;
	}
};

class Vector2D{
	public:
		float x;
		float y;

		static Vector2D zero;
		static Vector2D right;
		static Vector2D up;
		static Vector2D left;
		static Vector2D down;

		Vector2D(){
			setValues(0.0f, 0.0f);
		}
		Vector2D(float x, float y){
			setValues(x, y);
		}

		void setValues(float x, float y){
			this->x = x;
			this->y = y;
		}

		float getSquaredMagnitude(){
			return x * x + y * y;
		}

		float getMagnitude(){
			return sqrt(x * x + y * y);
		}

		Vector2D getNormalized(){
			float magnitude = getMagnitude();
			
			return Vector2D(x / magnitude, y / magnitude);
		}

		static float getInnerProduct(const Vector2D& a, const Vector2D& b);

		static Vector2D lerp(const Vector2D& a, const Vector2D& b, float f);

		class Vector3D toVector3D();
		static class Vector3D toVector3D(const Vector2D& vector);

		std::string toString();
		static std::string toString(const Vector2D& vector);

		D3DXVECTOR2 toD3DXVECTOR2();
		static D3DXVECTOR2 toD3DXVECTOR2(const Vector2D& vector);

	private:
		friend Vector2D operator +(const Vector2D& left, const Vector2D& right){
			return Vector2D(left.x + right.x, left.y + right.y);
		}

		friend Vector2D operator -(const Vector2D& left, const Vector2D& right){
			return Vector2D(left.x - right.x, left.y - right.y);
		}

		friend Vector2D operator *(const Vector2D& left, const Vector2D& right){
			return Vector2D(left.x * right.x, left.y * right.y);
		}

		friend Vector2D operator *(const Vector2D& vector, float scalar){
			return Vector2D(vector.x * scalar, vector.y * scalar);
		}

		friend Vector2D operator *(float scalar, const Vector2D& vector){
			return Vector2D(vector.x * scalar, vector.y * scalar);
		}

		friend bool operator ==(const Vector2D& left, const Vector2D& right){
			return left.x == right.x && left.y == right.y;
		}

		Vector2D& operator =(const class Vector3D& right);

		Vector2D& operator *=(float scalar){
			x *= scalar;
			y *= scalar;

			return *this;
		}

		Vector2D& operator +=(const Vector2D& right){
			x += right.x;
			y += right.y;

			return *this;
		}

		Vector2D& operator -=(const Vector2D& right){
			x -= right.x;
			y -= right.y;

			return *this;
		}
};

class Vector3D{
	public:
		float x;
		float y;
		float z;

		static Vector3D zero;
		static Vector3D right;
		static Vector3D up;
		static Vector3D forward;
		static Vector3D left;
		static Vector3D down;
		static Vector3D back;

		Vector3D(){
			setValue(0.0f, 0.0f, 0.0f);
		}
		Vector3D(float x, float y, float z){
			setValue(x, y, z);
		}

		void setValue(float x, float y, float z){
			this->x = x;
			this->y = y;
			this->z = z;
		}

		float getSquaredMagnitude(){
			return x * x + y * y + z * z;
		}

		float getMagnitude(){
			return sqrt(x * x + y * y + z * z);
		}

		Vector3D getNormalized(){
			float magnitude = getMagnitude();
			
			return Vector3D(x / magnitude, y / magnitude, z / magnitude);
		}

		static float getInnerProduct(const Vector3D& a, const Vector3D& b);
		static Vector3D getVectorProduct(const Vector3D& a, const Vector3D& b);

		static Vector3D lerp(const Vector3D& a, const Vector3D& b, float f);

		Vector3D transform(const class Matrix4x4& matrix, float w = 1.0f);
		static Vector3D transform(const Vector3D& vector, const class Matrix4x4& matrix, float w = 1.0f);

		class Vector2D toVector2D();
		static class Vector2D toVector2D(const Vector3D& vector);

		class Quaternion toQuaternion();
		static class Quaternion toQuaternion(const Vector3D& angles);

		std::string toString();
		static std::string toString(const Vector3D& vector);

		D3DXVECTOR3 toD3DXVECTOR3();
		static D3DXVECTOR3 toD3DXVECTOR3(const Vector3D& vector);

	private:
		friend Vector3D operator +(const Vector3D& left, const Vector3D& right){
			return Vector3D(left.x + right.x, left.y + right.y, left.z + right.z);
		}

		friend Vector3D operator -(const Vector3D& left, const Vector3D& right){
			return Vector3D(left.x - right.x, left.y - right.y, left.z - left.z);
		}

		friend Vector3D operator *(const Vector3D& left, const Vector3D& right){
			return Vector3D(left.x * right.x, left.y * right.y, left.z * right.z);
		}

		friend Vector3D operator *(const Vector3D& vector, float scalar){
			return Vector3D(vector.x * scalar, vector.y * scalar, vector.z * scalar);
		}

		friend Vector3D operator *(float scalar, const Vector3D& vector){
			return Vector3D(vector.x * scalar, vector.y * scalar, vector.z * scalar);
		}

		friend bool operator ==(const Vector3D& left, const Vector3D& right){
			return left.x == right.x && left.y == right.y && left.z == right.z;
		}

		Vector3D& operator *=(float scalar){
			x *= scalar;
			y *= scalar;
			z *= scalar;

			return *this;
		}

		Vector3D& operator +=(const Vector3D& right){
			x += right.x;
			y += right.y;
			z += right.z;

			return *this;
		}

		Vector3D& operator -=(const Vector3D& right){
			x -= right.x;
			y -= right.y;
			z -= right.z;

			return *this;
		}
};

class Quaternion{
	public:
		float x;
		float y;
		float z;
		float w;

		static Quaternion identity;

		Quaternion(){
			Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
		}
		Quaternion(float x, float y, float z, float w){
			setValues(x, y, z, w);
		}
		Quaternion(float angle, const Vector3D& axis){
			setValues(axis.x * Math::getSine(angle / 2.0f), axis.y * Math::getSine(angle / 2.0f), axis.z * Math::getSine(angle / 2.0f), Math::getCosine(angle / 2.0f));
		}

		void setValues(float x, float y, float z, float w){
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		float getSquaredMagnitude(){
			return x * x + y * y + z * z + w * w;
		}

		float getMagnitude(){
			return sqrt(x * x + y * y + z * z + w * w);
		}

		Quaternion getNormalized(){
			float magnitude = getMagnitude();
			
			return Quaternion(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
		}

		static float getInnerProduct(const Quaternion& a, const Quaternion& b);

		static float getAngle(const Quaternion& a, const Quaternion& b);
		
		static Quaternion concatenate(const Quaternion& q, const Quaternion& p);
		
		static Quaternion lerp(const Quaternion& a, const Quaternion& b, float f);
		static Quaternion slerp(const Quaternion& a, const Quaternion& b, float f);
		
		class Vector3D toEulerAngles();
		static class Vector3D toEulerAngles(const Quaternion& quaternion);

		std::string toString();
		static std::string toString(const Quaternion& quaternion);

		D3DXQUATERNION toD3DXQUATERNION();
		static D3DXQUATERNION toD3DXQUATERNION(const Quaternion& quaternion);

	private:
		friend Quaternion operator *(const Quaternion& left, const Quaternion& right){
			return Quaternion(
				left.x * right.w + left.w * right.x - left.z * right.y + left.y * right.z,
				left.y * right.w + left.z * right.x + left.w * right.y - left.x * right.z,
				left.z * right.w - left.y * right.x + left.x * right.y + left.w * right.z,
				left.w * right.w - left.x * right.x - left.y * right.y - left.z * right.z
			);
		}

		friend bool operator ==(const Quaternion& left, const Quaternion& right){
			return Math::areApproximate(Quaternion::getInnerProduct(left, right), 1.0f);
		}

		Quaternion& operator *=(const Quaternion& quaternion){
			x = x * quaternion.w + w * quaternion.x - z * quaternion.y + y * quaternion.z;
			y = y * quaternion.w + z * quaternion.x + w * quaternion.y - x * quaternion.z;
			z = z * quaternion.w - y * quaternion.x + x * quaternion.y + w * quaternion.z;
			w = w * quaternion.w - x * quaternion.x - y * quaternion.y - z * quaternion.z;

			return *this;
		}
};

class Matrix3x3{
	public:
		float matrix[3][3];

		static const Matrix3x3 identity;

		Matrix3x3(){
			*this = Matrix3x3::identity;
		}
		explicit Matrix3x3(float matrix[3][3]){
			memcpy(this->matrix, matrix, 9 * sizeof(float));
		}

		const float* getAsFloatPointer() const{
			return reinterpret_cast<const float*>(&matrix[0][0]);
		}

		friend Matrix3x3 operator*(const Matrix3x3& left, const Matrix3x3& right){
			Matrix3x3 temporal;

			temporal.matrix[0][0] = 
				left.matrix[0][0] * right.matrix[0][0] +
				left.matrix[0][1] * right.matrix[1][0] +
				left.matrix[0][2] * right.matrix[2][0];

			temporal.matrix[0][1] = 
				left.matrix[0][0] * right.matrix[0][1] +
				left.matrix[0][1] * right.matrix[1][1] +
				left.matrix[0][2] * right.matrix[2][1];

			temporal.matrix[0][2] = 
				left.matrix[0][0] * right.matrix[0][2] +
				left.matrix[0][1] * right.matrix[1][2] +
				left.matrix[0][2] * right.matrix[2][2];
		
			temporal.matrix[1][0] = 
				left.matrix[1][0] * right.matrix[0][0] +
				left.matrix[1][1] * right.matrix[1][0] +
				left.matrix[1][2] * right.matrix[2][0];

			temporal.matrix[1][1] = 
				left.matrix[1][0] * right.matrix[0][1] +
				left.matrix[1][1] * right.matrix[1][1] +
				left.matrix[1][2] * right.matrix[2][1];

			temporal.matrix[1][2] = 
				left.matrix[1][0] * right.matrix[0][2] +
				left.matrix[1][1] * right.matrix[1][2] +
				left.matrix[1][2] * right.matrix[2][2];
		
			temporal.matrix[2][0] = 
				left.matrix[2][0] * right.matrix[0][0] +
				left.matrix[2][1] * right.matrix[1][0] +
				left.matrix[2][2] * right.matrix[2][0];

			temporal.matrix[2][1] =
				left.matrix[2][0] * right.matrix[0][1] +
				left.matrix[2][1] * right.matrix[1][1] +
				left.matrix[2][2] * right.matrix[2][1];

			temporal.matrix[2][2] = 
				left.matrix[2][0] * right.matrix[0][2] +
				left.matrix[2][1] * right.matrix[1][2] +
				left.matrix[2][2] * right.matrix[2][2];

			return temporal;
		}

		Matrix3x3& operator*=(const Matrix3x3& right){
			*this = *this * right;
			return *this;
		}

		static Matrix3x3 getScalingMatrix(float x, float y);
		static Matrix3x3 getScalingMatrix(const class Vector2D& scale);
		static Matrix3x3 getScalingMatrix(float scale);

		static Matrix3x3 getRotationMatrix(float radian);

		static Matrix3x3 getTranslationMatrix(const class Vector2D& translation);
};

class Matrix4x4{
	public:
		float matrix[4][4];

		static const Matrix4x4 identity;

		Matrix4x4(){
			*this = Matrix4x4::identity;
		}
		explicit Matrix4x4(float matrix[4][4]){
			memcpy(this->matrix, matrix, 16 * sizeof(float));
		}

		const float* getAsFloatPointer() const{
			return reinterpret_cast<const float*>(&matrix[0][0]);
		}

		friend Matrix4x4 operator*(const Matrix4x4& left, const Matrix4x4& right){
			Matrix4x4 temporal;

			temporal.matrix[0][0] = 
				left.matrix[0][0] * right.matrix[0][0] + 
				left.matrix[0][1] * right.matrix[1][0] + 
				left.matrix[0][2] * right.matrix[2][0] +
				left.matrix[0][3] * right.matrix[3][0];

			temporal.matrix[0][1] = 
				left.matrix[0][0] * right.matrix[0][1] + 
				left.matrix[0][1] * right.matrix[1][1] + 
				left.matrix[0][2] * right.matrix[2][1] + 
				left.matrix[0][3] * right.matrix[3][1];

			temporal.matrix[0][2] = 
				left.matrix[0][0] * right.matrix[0][2] + 
				left.matrix[0][1] * right.matrix[1][2] + 
				left.matrix[0][2] * right.matrix[2][2] + 
				left.matrix[0][3] * right.matrix[3][2];
		
			temporal.matrix[0][3] = 
				left.matrix[0][0] * right.matrix[0][3] + 
				left.matrix[0][1] * right.matrix[1][3] + 
				left.matrix[0][2] * right.matrix[2][3] + 
				left.matrix[0][3] * right.matrix[3][3];

			temporal.matrix[1][0] = 
				left.matrix[1][0] * right.matrix[0][0] + 
				left.matrix[1][1] * right.matrix[1][0] + 
				left.matrix[1][2] * right.matrix[2][0] + 
				left.matrix[1][3] * right.matrix[3][0];

			temporal.matrix[1][1] = 
				left.matrix[1][0] * right.matrix[0][1] + 
				left.matrix[1][1] * right.matrix[1][1] + 
				left.matrix[1][2] * right.matrix[2][1] + 
				left.matrix[1][3] * right.matrix[3][1];

			temporal.matrix[1][2] = 
				left.matrix[1][0] * right.matrix[0][2] + 
				left.matrix[1][1] * right.matrix[1][2] + 
				left.matrix[1][2] * right.matrix[2][2] + 
				left.matrix[1][3] * right.matrix[3][2];

			temporal.matrix[1][3] = 
				left.matrix[1][0] * right.matrix[0][3] +
				left.matrix[1][1] * right.matrix[1][3] +
				left.matrix[1][2] * right.matrix[2][3] +
				left.matrix[1][3] * right.matrix[3][3];

			temporal.matrix[2][0] = 
				left.matrix[2][0] * right.matrix[0][0] +
				left.matrix[2][1] * right.matrix[1][0] +
				left.matrix[2][2] * right.matrix[2][0] +
				left.matrix[2][3] * right.matrix[3][0];

			temporal.matrix[2][1] = 
				left.matrix[2][0] * right.matrix[0][1] + 
				left.matrix[2][1] * right.matrix[1][1] + 
				left.matrix[2][2] * right.matrix[2][1] + 
				left.matrix[2][3] * right.matrix[3][1];

			temporal.matrix[2][2] = 
				left.matrix[2][0] * right.matrix[0][2] +
				left.matrix[2][1] * right.matrix[1][2] + 
				left.matrix[2][2] * right.matrix[2][2] + 
				left.matrix[2][3] * right.matrix[3][2];

			temporal.matrix[2][3] = 
				left.matrix[2][0] * right.matrix[0][3] + 
				left.matrix[2][1] * right.matrix[1][3] + 
				left.matrix[2][2] * right.matrix[2][3] + 
				left.matrix[2][3] * right.matrix[3][3];

			temporal.matrix[3][0] = 
				left.matrix[3][0] * right.matrix[0][0] + 
				left.matrix[3][1] * right.matrix[1][0] + 
				left.matrix[3][2] * right.matrix[2][0] + 
				left.matrix[3][3] * right.matrix[3][0];

			temporal.matrix[3][1] = 
				left.matrix[3][0] * right.matrix[0][1] + 
				left.matrix[3][1] * right.matrix[1][1] + 
				left.matrix[3][2] * right.matrix[2][1] + 
				left.matrix[3][3] * right.matrix[3][1];

			temporal.matrix[3][2] = 
				left.matrix[3][0] * right.matrix[0][2] +
				left.matrix[3][1] * right.matrix[1][2] +
				left.matrix[3][2] * right.matrix[2][2] +
				left.matrix[3][3] * right.matrix[3][2];

			temporal.matrix[3][3] = 
				left.matrix[3][0] * right.matrix[0][3] +
				left.matrix[3][1] * right.matrix[1][3] +
				left.matrix[3][2] * right.matrix[2][3] +
				left.matrix[3][3] * right.matrix[3][3];
		
			return temporal;
		}

		Matrix4x4& operator*=(const Matrix4x4& right){
			*this = *this * right;
			return *this;
		}

		static Matrix4x4 getWorldMatrix(class TransformComponent* transform);

		static Matrix4x4 getScalingMatrix(const class Vector3D& scale);
		static Matrix4x4 getRotationMatrix(const Matrix4x4& transform, const class Quaternion& rotation);
		static Matrix4x4 getTranslationMatrix(const Matrix4x4& transform, const class Vector3D& translation);

		static Matrix4x4 getViewMatrix(const class Vector3D& cameraPosition, const class Vector3D& lookPosition, const class Vector3D& upVector);

		//static Matrix4x4 getProjectionMatrix();

		D3DXMATRIX toD3DXMATRIX();
		static D3DXMATRIX toD3DXMATRIX(const Matrix4x4& matrix);
};
