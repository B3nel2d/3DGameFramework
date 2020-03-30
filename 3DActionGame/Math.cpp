#include "Math.h"
#include "TransformComponent.h"

Vector2D Vector2D::zero = Vector2D(0.0f, 0.0f);
Vector2D Vector2D::right = Vector2D(1.0f, 0.0f);
Vector2D Vector2D::up = Vector2D(0.0f, 1.0f);
Vector2D Vector2D::left = Vector2D(-1.0f, 0.0f);
Vector2D Vector2D::down = Vector2D(0.0f, -1.0f);

/**********************************************************************
	getInnerProduct

	内積を取得する
**********************************************************************/
float Vector2D::getInnerProduct(const Vector2D& a, const Vector2D& b){
	return a.x * b.x + a.y * b.y;
}

/**********************************************************************
	lerp

	線形補完を行う
**********************************************************************/
Vector2D Vector2D::lerp(const Vector2D& a, const Vector2D& b, float f){
	return Vector2D(a + f * (b - a));
}

/**********************************************************************
	toVector3D

	Vector3Dへ変換し取得する
**********************************************************************/
Vector3D Vector2D::toVector3D(){
	return Vector3D(x, y, 0.0f);
}
Vector3D Vector2D::toVector3D(const Vector2D& vector){
	return Vector3D(vector.x, vector.y, 0.0f);
}

/**********************************************************************
	toString

	stringへ変換し取得する
**********************************************************************/
string Vector2D::toString(){
	std::string string = "";
	string += "(x: ";
	string += std::to_string(x);
	string += " y: ";
	string += std::to_string(y);
	string += ")";

	return string;
}
string Vector2D::toString(const Vector2D& vector){
	std::string string = "";
	string += "(x: ";
	string += std::to_string(vector.x);
	string += " y: ";
	string += std::to_string(vector.y);
	string += ")";

	return string;
}

/**********************************************************************
	toD3DXVECTOR2

	D3DXVECTOR2へ変換し取得する
**********************************************************************/
D3DXVECTOR2 Vector2D::toD3DXVECTOR2(){
	return D3DXVECTOR2(x, y);
}
D3DXVECTOR2 Vector2D::toD3DXVECTOR2(const Vector2D& vector){
	return D3DXVECTOR2(vector.x, vector.y);
}

/**********************************************************************
	演算子 =

	演算子の右を左に代入する
**********************************************************************/
Vector2D& Vector2D::operator =(const Vector3D& right){
	x = right.x;
	y = right.y;

	return *this;
}

Vector3D Vector3D::zero = Vector3D(0.0f, 0.0f, 0.0f);
Vector3D Vector3D::right = Vector3D(1.0f, 0.0f, 0.0f);
Vector3D Vector3D::up = Vector3D(0.0f, 1.0f, 0.0f);
Vector3D Vector3D::forward = Vector3D(0.0f, 0.0f, 1.0f);
Vector3D Vector3D::left = Vector3D(-1.0f, 0.0f, 0.0f);
Vector3D Vector3D::down = Vector3D(0.0f, -1.0f, 0.0f);
Vector3D Vector3D::back = Vector3D(0.0f, 0.0f, -1.0f);

/**********************************************************************
	getInnerProduct

	内積を取得する
**********************************************************************/
float Vector3D::getInnerProduct(const Vector3D& a, const Vector3D& b){
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

/**********************************************************************
	getVectorProduct

	外積を取得する
**********************************************************************/
Vector3D Vector3D::getVectorProduct(const Vector3D& a, const Vector3D& b){
	return Vector3D(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

/**********************************************************************
	lerp

	線形補間を行う
**********************************************************************/
Vector3D Vector3D::lerp(const Vector3D& a, const Vector3D& b, float f){
	return Vector3D(a + f * (b - a));
}

/**********************************************************************
	transform

	行列変換を行う
**********************************************************************/
Vector3D Vector3D::transform(const Matrix4x4& matrix, float w){
	return transform(Vector3D(x, y, z), matrix, w);
}
Vector3D Vector3D::transform(const Vector3D& vector, const Matrix4x4& matrix, float w){
	Vector3D transformedVector;
	transformedVector.x = vector.x * matrix.matrix[0][0] + vector.y * matrix.matrix[1][0] + vector.z * matrix.matrix[2][0] + w * matrix.matrix[3][0];
	transformedVector.y = vector.x * matrix.matrix[0][1] + vector.y * matrix.matrix[1][1] + vector.z * matrix.matrix[2][1] + w * matrix.matrix[3][1];
	transformedVector.z = vector.x * matrix.matrix[0][2] + vector.y * matrix.matrix[1][2] + vector.z * matrix.matrix[2][2] + w * matrix.matrix[3][2];

	return transformedVector;
}

/**********************************************************************
	toVector2D

	Vector2Dへ変換し取得する
**********************************************************************/
Vector2D Vector3D::toVector2D(){
	return Vector2D(x, y);
}
Vector2D Vector3D::toVector2D(const Vector3D& vector){
	return Vector2D(vector.x, vector.y);
}

/**********************************************************************
	toQuaternion

	Quaternionへ変換し取得する
**********************************************************************/
Quaternion Vector3D::toQuaternion(){
	float x = Math::getSine(this->x / 2.0f) * Math::getCosine(this->y / 2.0f) * Math::getCosine(this->z / 2.0f) - Math::getCosine(this->x / 2.0f) * Math::getSine(this->y / 2.0f) * Math::getSine(this->z / 2.0f);
	float y = Math::getCosine(this->x / 2.0f) * Math::getSine(this->y / 2.0f) * Math::getCosine(this->z / 2.0f) + Math::getSine(this->x / 2.0f) * Math::getCosine(this->y / 2.0f) * Math::getSine(this->z / 2.0f);
	float z = Math::getCosine(this->x / 2.0f) * Math::getCosine(this->y / 2.0f) * Math::getSine(this->z / 2.0f) - Math::getSine(this->x / 2.0f) * Math::getSine(this->y / 2.0f) * Math::getCosine(this->z / 2.0f);
	float w = Math::getCosine(this->x / 2.0f) * Math::getCosine(this->y / 2.0f) * Math::getCosine(this->z / 2.0f) + Math::getSine(this->x / 2.0f) * Math::getSine(this->y / 2.0f) * Math::getSine(this->z / 2.0f);

	return Quaternion(x, y, z, w);
}
Quaternion Vector3D::toQuaternion(const Vector3D& angles){
	float x = Math::getSine(angles.x / 2.0f) * Math::getCosine(angles.y / 2.0f) * Math::getCosine(angles.z / 2.0f) - Math::getCosine(angles.x / 2.0f) * Math::getSine(angles.y / 2.0f) * Math::getSine(angles.z / 2.0f);
	float y = Math::getCosine(angles.x / 2.0f) * Math::getSine(angles.y / 2.0f) * Math::getCosine(angles.z / 2.0f) + Math::getSine(angles.x / 2.0f) * Math::getCosine(angles.y / 2.0f) * Math::getSine(angles.z / 2.0f);
	float z = Math::getCosine(angles.x / 2.0f) * Math::getCosine(angles.y / 2.0f) * Math::getSine(angles.z / 2.0f) - Math::getSine(angles.x / 2.0f) * Math::getSine(angles.y / 2.0f) * Math::getCosine(angles.z / 2.0f);
	float w = Math::getCosine(angles.x / 2.0f) * Math::getCosine(angles.y / 2.0f) * Math::getCosine(angles.z / 2.0f) + Math::getSine(angles.x / 2.0f) * Math::getSine(angles.y / 2.0f) * Math::getSine(angles.z / 2.0f);

	return Quaternion(x, y, z, w);
}

/**********************************************************************
	toString

	stringへ変換し取得する
**********************************************************************/
string Vector3D::toString(){
	std::string string = "";
	string += "(x: ";
	string += std::to_string(x);
	string += " y: ";
	string += std::to_string(y);
	string += " z: ";
	string += std::to_string(z);
	string += ")";

	return string;
}
string Vector3D::toString(const Vector3D& vector){
	std::string string = "";
	string += "(x: ";
	string += std::to_string(vector.x);
	string += " y: ";
	string += std::to_string(vector.y);
	string += " z: ";
	string += std::to_string(vector.z);
	string += ")";

	return string;
}

/**********************************************************************
	toD3DXVECTOR3

	D3DXVECTOR3へ変換し取得する
**********************************************************************/
D3DXVECTOR3 Vector3D::toD3DXVECTOR3(){
	return D3DXVECTOR3(x, y, z);
}
D3DXVECTOR3 Vector3D::toD3DXVECTOR3(const Vector3D& vector){
	return D3DXVECTOR3(vector.x, vector.y, vector.z);
}

Quaternion Quaternion::identity = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

/**********************************************************************
	getInnerProduct

	内積を取得する
**********************************************************************/
float Quaternion::getInnerProduct(const Quaternion& a, const Quaternion& b){
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

/**********************************************************************
	getAngle
	
	二回転間の角度を求める
**********************************************************************/
float Quaternion::getAngle(const Quaternion& a, const Quaternion& b){
	return Math::getArcCosine(getInnerProduct(a, b));
}

/**********************************************************************
	concatenate

	二つの四元数を連結する
**********************************************************************/
Quaternion Quaternion::concatenate(const Quaternion& q, const Quaternion& p){
	Vector3D a = Vector3D(q.x, q.y, q.z);
	Vector3D b = Vector3D(p.x, p.y, p.z);
	Vector3D c = Vector3D(p.w * a + q.w * b + Vector3D::getVectorProduct(b, a));

	return Quaternion(c.x, c.y, c.z, q.w * p.w - Vector3D::getInnerProduct(b, a));
}

/**********************************************************************
	lerp

	線形補間を行う
**********************************************************************/
Quaternion Quaternion::lerp(const Quaternion& a, const Quaternion& b, float f){
	return Quaternion(Math::lerp(a.x, b.x, f), Math::lerp(a.y, b.y, f), Math::lerp(a.z, b.z, f), Math::lerp(a.w, b.w, f)).getNormalized();
}

/**********************************************************************
	slerp

	球面補完を行う
**********************************************************************/
Quaternion Quaternion::slerp(const Quaternion& a, const Quaternion& b, float f){
	float cosineOmega = Quaternion::getInnerProduct(a, b);
	bool isDotNegative = false;
	float scale[2];

	if(cosineOmega < 0.0f){
		cosineOmega *= -1.0f;
		isDotNegative = true;
	}

	if(cosineOmega < 0.9999f){
		scale[0] = 1.0f - f;
		scale[1] = f;
	}
	else{
		float omega = Math::getArcCosine(cosineOmega);

		scale[0] = Math::getSine((1.0f - f) * omega) * (1.0f / Math::getSine(omega));
		scale[1] = Math::getSine(f * omega) * (1.0f / Math::getSine(omega));
	}

	if(isDotNegative){
		scale[1] *= -1.0f;
	}

	return Quaternion(a.x * scale[0] + b.x * scale[1], a.y * scale[0] + b.y * scale[1], a.z * scale[0] + b.z * scale[1], a.w * scale[0] + b.w * scale[1]).getNormalized();
}

/**********************************************************************
	toEulerAngles

	オイラー角を取得する
**********************************************************************/
Vector3D Quaternion::toEulerAngles(){
	float roll = Math::getArcTangent(2.0f * (y * z + w * x), w * w - x * x - y * y + z * z);
	float pitch = Math::getArcSine(2.0f * (w * y - x * z));
	float yaw = Math::getArcTangent(2.0f * (x * y + w * z), w * w + x * x - y * y - z * z);

	return Vector3D(roll, pitch, yaw);
}
Vector3D Quaternion::toEulerAngles(const Quaternion& quaternion){
	float roll = Math::getArcTangent(2.0f * (quaternion.y * quaternion.z + quaternion.w * quaternion.x), quaternion.w * quaternion.w - quaternion.x * quaternion.x - quaternion.y * quaternion.y + quaternion.z * quaternion.z);
	float pitch = Math::getArcSine(2.0f * (quaternion.w * quaternion.y - quaternion.x * quaternion.z));
	float yaw = Math::getArcTangent(2.0f * (quaternion.x * quaternion.y + quaternion.w * quaternion.z), quaternion.w * quaternion.w + quaternion.x * quaternion.x - quaternion.y * quaternion.y - quaternion.z * quaternion.z);

	return Vector3D(roll, pitch, yaw);
}

/**********************************************************************
	toString

	stringへ変換し取得する
**********************************************************************/
string Quaternion::toString(){
	std::string string = "";
	string += "(w: ";
	string += std::to_string(w);
	string += " x: ";
	string += std::to_string(x);
	string += " y: ";
	string += std::to_string(y);
	string += " z: ";
	string += std::to_string(z);
	string += ")";

	return string;
}
string Quaternion::toString(const Quaternion& quaternion){
	std::string string = "";
	string += "(x: ";
	string += std::to_string(quaternion.x);
	string += " y: ";
	string += std::to_string(quaternion.y);
	string += " z: ";
	string += std::to_string(quaternion.z);
	string += " w: ";
	string += std::to_string(quaternion.w);
	string += ")";

	return string;
}

/**********************************************************************
	toD3DXQUATERNION

	D3DXQUATERNIONへ変換し取得する
**********************************************************************/
D3DXQUATERNION Quaternion::toD3DXQUATERNION(){
	return D3DXQUATERNION(x, y, z, w);
}
D3DXQUATERNION Quaternion::toD3DXQUATERNION(const Quaternion& quaternion){
	return D3DXQUATERNION(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
}

static float identity3x3[3][3] = {
	{1.0f, 0.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 0.0f, 1.0f}
};

const Matrix3x3 Matrix3x3::identity(identity3x3);

/**********************************************************************
	getScalingMatrix

	拡大縮小行列を取得する
**********************************************************************/
Matrix3x3 Matrix3x3::getScalingMatrix(float x, float y){
	float temporal[3][3] = {
		{x, 0.0f, 0.0f},
		{0.0f, y, 0.0f},
		{0.0f, 0.0f, 1.0f},
	};

	return Matrix3x3(temporal);
}
Matrix3x3 Matrix3x3::getScalingMatrix(const Vector2D& scale){
	return getScalingMatrix(scale.x, scale.y);
}
Matrix3x3 Matrix3x3::getScalingMatrix(float scale){
	return getScalingMatrix(scale, scale);
}

/**********************************************************************
	getRotationMatrix

	回転行列を取得する
**********************************************************************/
Matrix3x3 Matrix3x3::getRotationMatrix(float radian){
	float temporal[3][3] = {
		{Math::getCosine(radian), Math::getSine(radian), 0.0f},
		{-Math::getSine(radian), Math::getCosine(radian), 0.0f},
		{0.0f, 0.0f, 1.0f},
	};

	return Matrix3x3(temporal);
}

/**********************************************************************
	getTranslationMatrix

	平行移動行列を取得する
**********************************************************************/
Matrix3x3 Matrix3x3::getTranslationMatrix(const Vector2D& translation){
	float temporal[3][3] = {
		{1.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{translation.x, translation.y, 1.0f},
	};

	return Matrix3x3(temporal);
}

static float identity4x4[4][4] = {
	{1.0f, 0.0f, 0.0f, 0.0f},
	{0.0f, 1.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 1.0f, 0.0f},
	{0.0f, 0.0f, 0.0f, 1.0f}
};

const Matrix4x4 Matrix4x4::identity(identity4x4);

/**********************************************************************
	getWorldMatrix

	ワールド座標変換行列を取得する
**********************************************************************/
Matrix4x4 Matrix4x4::getWorldMatrix(TransformComponent* transform){
	Matrix4x4 scalingMatrix = getScalingMatrix(transform->getScale());
	Matrix4x4 rotationMatrix = getRotationMatrix(scalingMatrix, transform->getRotation());
	Matrix4x4 translationMatrix = getTranslationMatrix(rotationMatrix, transform->getPosition());

	Matrix4x4 worldMatrix = Matrix4x4();
	worldMatrix = scalingMatrix * rotationMatrix;
	worldMatrix = worldMatrix * translationMatrix;

	return worldMatrix;
}

/**********************************************************************
	getScalingMatrix

	拡大縮小行列を取得する
**********************************************************************/
Matrix4x4 Matrix4x4::getScalingMatrix(const Vector3D& scale){
	float temporal[4][4] = {
		{scale.x, 0.0f, 0.0f, 0.0f},
		{0.0f, scale.y, 0.0f, 0.0f},
		{0.0f, 0.0f, scale.z, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}
	};

	return Matrix4x4(temporal);
}

/**********************************************************************
	getRotationMatrix

	回転行列を取得する
**********************************************************************/
Matrix4x4 Matrix4x4::getRotationMatrix(const Matrix4x4& transform, const Quaternion& rotation){
	Matrix4x4 temporal = transform;
	Vector3D angles = Quaternion::toEulerAngles(rotation);

	float rotationMatrixX[4][4] = {
		{1.0f, 0.0f, 0.0f , 0.0f},
		{0.0f, Math::getCosine(angles.x), Math::getSine(angles.x), 0.0f},
		{0.0f, -Math::getSine(angles.x), Math::getCosine(angles.x), 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f},
	};

	float rotationMatrixY[4][4] = {
		{Math::getCosine(angles.y), 0.0f, -Math::getSine(angles.y), 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{Math::getSine(angles.y), 0.0f, Math::getCosine(angles.y), 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f},
	};

	float rotationMatrixZ[4][4] = {
		{Math::getCosine(angles.z), Math::getSine(angles.z), 0.0f, 0.0f},
		{-Math::getSine(angles.z), Math::getCosine(angles.z), 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f},
	};

	temporal *= Matrix4x4(rotationMatrixX);
	temporal *= Matrix4x4(rotationMatrixY);
	temporal *= Matrix4x4(rotationMatrixZ);

	return temporal;
}

/**********************************************************************
	getTranslationMatrix

	平行移動行列を取得する
**********************************************************************/
Matrix4x4 Matrix4x4::getTranslationMatrix(const Matrix4x4& transform, const Vector3D& translation){
	float temporal[4][4] = {
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{translation.x, translation.y, translation.z, 1.0f}
	};

	return transform * Matrix4x4(temporal);
}

/**********************************************************************
	getViewMatrix

	ビュー座標変換行列を取得する
**********************************************************************/
Matrix4x4 Matrix4x4::getViewMatrix(const Vector3D& cameraPosition, const Vector3D& lookPosition, const Vector3D& upVector){
	Vector3D xAxis = Vector3D();
	Vector3D yAxis = Vector3D();
	Vector3D zAxis = Vector3D();

	zAxis = (lookPosition - cameraPosition).getNormalized();
	xAxis = (Vector3D::getVectorProduct(upVector, zAxis)).getNormalized();
	yAxis = (Vector3D::getVectorProduct(zAxis, xAxis)).getNormalized();

	float viewMatrix[4][4] = {
		{xAxis.x, yAxis.x, zAxis.x, -Vector3D::getInnerProduct(cameraPosition, xAxis)},
		{xAxis.y, yAxis.y, zAxis.y, -Vector3D::getInnerProduct(cameraPosition, yAxis)},
		{xAxis.z, yAxis.z, zAxis.z, -Vector3D::getInnerProduct(cameraPosition, zAxis)},
		{0.0f, 0.0f, 0.0f, 1.0f}
	};

	return Matrix4x4(viewMatrix);
}

/**********************************************************************
	toD3DXMATRIX

	D3DXMATRIXへ変換し取得する
**********************************************************************/
D3DXMATRIX Matrix4x4::toD3DXMATRIX(){
	return D3DXMATRIX(getAsFloatPointer());
}
D3DXMATRIX Matrix4x4::toD3DXMATRIX(const Matrix4x4& matrix){
	return D3DXMATRIX(matrix.getAsFloatPointer());
}
