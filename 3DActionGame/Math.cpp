#include "Math.h"
#include "TransformComponent.h"

Vector2D Vector2D::zero = Vector2D(0.0f, 0.0f);
Vector2D Vector2D::right = Vector2D(1.0f, 0.0f);
Vector2D Vector2D::up = Vector2D(0.0f, 1.0f);
Vector2D Vector2D::left = Vector2D(-1.0f, 0.0f);
Vector2D Vector2D::down = Vector2D(0.0f, -1.0f);

/**********************************************************************
	getInnerProduct

	���ς��擾����
**********************************************************************/
float Vector2D::getInnerProduct(const Vector2D& a, const Vector2D& b){
	return a.x * b.x + a.y * b.y;
}

/**********************************************************************
	lerp

	���`�⊮���s��
**********************************************************************/
Vector2D Vector2D::lerp(const Vector2D& a, const Vector2D& b, float f){
	return Vector2D(a + f * (b - a));
}

/**********************************************************************
	toVector3D

	Vector3D�֕ϊ����擾����
**********************************************************************/
Vector3D Vector2D::toVector3D(){
	return Vector3D(x, y, 0.0f);
}
Vector3D Vector2D::toVector3D(const Vector2D& vector){
	return Vector3D(vector.x, vector.y, 0.0f);
}

/**********************************************************************
	toString

	string�֕ϊ����擾����
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

	D3DXVECTOR2�֕ϊ����擾����
**********************************************************************/
D3DXVECTOR2 Vector2D::toD3DXVECTOR2(){
	return D3DXVECTOR2(x, y);
}
D3DXVECTOR2 Vector2D::toD3DXVECTOR2(const Vector2D& vector){
	return D3DXVECTOR2(vector.x, vector.y);
}

/**********************************************************************
	���Z�q =

	���Z�q�̉E�����ɑ������
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

	���ς��擾����
**********************************************************************/
float Vector3D::getInnerProduct(const Vector3D& a, const Vector3D& b){
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

/**********************************************************************
	getVectorProduct

	�O�ς��擾����
**********************************************************************/
Vector3D Vector3D::getVectorProduct(const Vector3D& a, const Vector3D& b){
	return Vector3D(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

/**********************************************************************
	lerp

	���`��Ԃ��s��
**********************************************************************/
Vector3D Vector3D::lerp(const Vector3D& a, const Vector3D& b, float f){
	return Vector3D(a + f * (b - a));
}

/**********************************************************************
	transform

	�s��ϊ����s��
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

	Vector2D�֕ϊ����擾����
**********************************************************************/
Vector2D Vector3D::toVector2D(){
	return Vector2D(x, y);
}
Vector2D Vector3D::toVector2D(const Vector3D& vector){
	return Vector2D(vector.x, vector.y);
}

/**********************************************************************
	toQuaternion

	Quaternion�֕ϊ����擾����
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

	string�֕ϊ����擾����
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

	D3DXVECTOR3�֕ϊ����擾����
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

	���ς��擾����
**********************************************************************/
float Quaternion::getInnerProduct(const Quaternion& a, const Quaternion& b){
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

/**********************************************************************
	getAngle
	
	���]�Ԃ̊p�x�����߂�
**********************************************************************/
float Quaternion::getAngle(const Quaternion& a, const Quaternion& b){
	return Math::getArcCosine(getInnerProduct(a, b));
}

/**********************************************************************
	concatenate

	��̎l������A������
**********************************************************************/
Quaternion Quaternion::concatenate(const Quaternion& q, const Quaternion& p){
	Vector3D a = Vector3D(q.x, q.y, q.z);
	Vector3D b = Vector3D(p.x, p.y, p.z);
	Vector3D c = Vector3D(p.w * a + q.w * b + Vector3D::getVectorProduct(b, a));

	return Quaternion(c.x, c.y, c.z, q.w * p.w - Vector3D::getInnerProduct(b, a));
}

/**********************************************************************
	lerp

	���`��Ԃ��s��
**********************************************************************/
Quaternion Quaternion::lerp(const Quaternion& a, const Quaternion& b, float f){
	return Quaternion(Math::lerp(a.x, b.x, f), Math::lerp(a.y, b.y, f), Math::lerp(a.z, b.z, f), Math::lerp(a.w, b.w, f)).getNormalized();
}

/**********************************************************************
	slerp

	���ʕ⊮���s��
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

	�I�C���[�p���擾����
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

	string�֕ϊ����擾����
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

	D3DXQUATERNION�֕ϊ����擾����
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

	�g��k���s����擾����
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

	��]�s����擾����
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

	���s�ړ��s����擾����
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

	���[���h���W�ϊ��s����擾����
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

	�g��k���s����擾����
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

	��]�s����擾����
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

	���s�ړ��s����擾����
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

	�r���[���W�ϊ��s����擾����
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

	D3DXMATRIX�֕ϊ����擾����
**********************************************************************/
D3DXMATRIX Matrix4x4::toD3DXMATRIX(){
	return D3DXMATRIX(getAsFloatPointer());
}
D3DXMATRIX Matrix4x4::toD3DXMATRIX(const Matrix4x4& matrix){
	return D3DXMATRIX(matrix.getAsFloatPointer());
}
