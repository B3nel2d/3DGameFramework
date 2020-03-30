#include "Collision.h"
#include <algorithm>
#include <array>

//======================================================================
//	LineSegment
//
//	線分のコリジョン
//======================================================================

/**********************************************************************
	コンストラクター
**********************************************************************/
LineSegment::LineSegment(){
	this->start = Vector3D::zero;
	this->end = Vector3D::zero;
}
LineSegment::LineSegment(const Vector3D& start, const Vector3D& end){
	this->start = start;
	this->end = end;
}

/**********************************************************************
	getPoint

	変数tに応じた線分上の点を取得する
**********************************************************************/
Vector3D LineSegment::getPoint(float t)const{
	return start +(end - start) * t;
}

/**********************************************************************
	getMinimumSquaredDistance

	点との最短距離を取得する
**********************************************************************/
float LineSegment::getMinimumSquaredDistance(const Vector3D& point)const{
	Vector3D ab = end - start;
	Vector3D ba = -1.0f * ab;
	Vector3D ac = point - start;
	Vector3D bc = point - end;

	if(Vector3D::getInnerProduct(ab, ac) < 0.0f){
		return ac.getSquaredMagnitude();
	}
	else if(Vector3D::getInnerProduct(ba, bc) < 0.0f){
		return bc.getSquaredMagnitude();
	}
	else{
		float scalar = Vector3D::getInnerProduct(ac, ab) / Vector3D::getInnerProduct(ab, ab);
		Vector3D p = scalar * ab;

		return(ac - p).getSquaredMagnitude();
	}
}
/**********************************************************************
	getMinimumSquaredDistance

	線分との最短距離を取得する
**********************************************************************/
float LineSegment::getMinimumSquaredDistance(const LineSegment& lineSegmentA, const LineSegment& lineSegmentB){
	Vector3D u = lineSegmentA.end - lineSegmentA.start;
	Vector3D v = lineSegmentB.end - lineSegmentB.start;
	Vector3D w = lineSegmentA.start - lineSegmentB.start;
	float a = Vector3D::getInnerProduct(u, u);
	float b = Vector3D::getInnerProduct(u, v);
	float c = Vector3D::getInnerProduct(v, v);
	float d = Vector3D::getInnerProduct(u, w);
	float e = Vector3D::getInnerProduct(v, w);
	float D = a * c - b * b;
	float sc, sN, sD = D;
	float tc, tN, tD = D;

	if(Math::areApproximate(D, 0.0f)){
		sN = 0.0f;
		sD = 1.0f;
		tN = e;
		tD = c;
	}
	else{
		sN = (b * e - c * d);
		tN = (a * e - b * d);

		if(sN < 0.0f){
			sN = 0.0f;
			tN = e;
			tD = c;
		}
		else if(sD < sN){
			sN = sD;
			tN = e + b;
			tD = c;
		}
	}

	if(tN < 0.0f){
		tN = 0.0f;

		if(-d < 0.0f){
			sN = 0.0f;
		}
		else if(a < -d){
			sN = sD;
		}
		else{
			sN = -d;
			sD = a;
		}
	}
	else if(tD < tN){
		tN = tD;

		if((-d + b) < 0.0f){
			sN = 0.0f;
		}
		else if(a < (-d + b)){
			sN = sD;
		}
		else{
			sN = (-d + b);
			sD = a;
		}
	}

	sc = (Math::areApproximate(sN, 0.0f) ? 0.0f : sN / sD);
	tc = (Math::areApproximate(tN, 0.0f) ? 0.0f : tN / tD);
	Vector3D difference = w + (sc * u) - (tc * v);

	return difference.getSquaredMagnitude();
}

//======================================================================
//	Plane
//
//	平面のコリジョン
//======================================================================

/**********************************************************************
	コンストラクター
**********************************************************************/
Plane::Plane(){
	this->normal = Vector3D::zero;
	this->signedMinimalDistance = 0.0f;
}
Plane::Plane(const Vector3D& normal, float signedMinimalDistance){
	this->normal = normal;
	this->signedMinimalDistance = signedMinimalDistance;
}
Plane::Plane(const Vector3D& a, const Vector3D& b, const Vector3D& c){
	Vector3D ab = b - a;
	Vector3D ac = c - a;

	normal = Vector3D::getVectorProduct(ab, ac);
	normal.getNormalized();

	this->signedMinimalDistance = -1.0f * Vector3D::getInnerProduct(a, normal);
}

/**********************************************************************
	getSignedDistance

	点との距離を取得する
**********************************************************************/
float Plane::getSignedDistance(const Vector3D& point) const{
	return Vector3D::getInnerProduct(point, normal) - signedMinimalDistance;
}

//======================================================================
//	Sphere
//
//	球体のコリジョン
//======================================================================

/**********************************************************************
	コンストラクター
**********************************************************************/
Sphere::Sphere(){
	this->center = Vector3D::zero;
	this->radius = 0.0f;
}
Sphere::Sphere(const Vector3D& center, float radius){
	this->center = center;
	this->radius = radius;
}

/**********************************************************************
	contains

	点を含んでいるか判定する
**********************************************************************/
bool Sphere::contains(const Vector3D& point) const{
	float squaredDistance = (center - point).getSquaredMagnitude();
	return squaredDistance <= (radius * radius);
}

//======================================================================
//	AxisAlignedBoundingBox
//
//	軸平行バウンディングボックスのコリジョン
//======================================================================

/**********************************************************************
	コンストラクター
**********************************************************************/
AxisAlignedBoundingBox::AxisAlignedBoundingBox(){
	this->maximumPoint = Vector3D::zero;
	this->minimumPoint = Vector3D::zero;
}
AxisAlignedBoundingBox::AxisAlignedBoundingBox(const Vector3D& minimumPoint, const Vector3D& maximumPoint){
	this->minimumPoint = minimumPoint;
	this->maximumPoint = maximumPoint;
}

/**********************************************************************
	updatePoints

	各頂点座標を更新する
**********************************************************************/
void AxisAlignedBoundingBox::updatePoints(const Vector3D& point){
	minimumPoint.x = Math::getMinimum(minimumPoint.x, point.x);
	minimumPoint.y = Math::getMinimum(minimumPoint.y, point.y);
	minimumPoint.z = Math::getMinimum(minimumPoint.z, point.z);

	maximumPoint.x = Math::getMaximum(maximumPoint.x, point.x);
	maximumPoint.y = Math::getMaximum(maximumPoint.y, point.y);
	maximumPoint.z = Math::getMaximum(maximumPoint.z, point.z);
}

/**********************************************************************
	rotate

	回転を適用する
**********************************************************************/
void AxisAlignedBoundingBox::rotate(const Quaternion& rotation){
	std::array<Vector3D, 8> points;
	points[0] = minimumPoint;
	points[1] = Vector3D(maximumPoint.x, minimumPoint.y, minimumPoint.z);
	points[2] = Vector3D(minimumPoint.x, maximumPoint.y, minimumPoint.z);
	points[3] = Vector3D(minimumPoint.x, minimumPoint.y, maximumPoint.z);
	points[4] = Vector3D(minimumPoint.x, maximumPoint.y, maximumPoint.z);
	points[5] = Vector3D(maximumPoint.x, minimumPoint.y, maximumPoint.z);
	points[6] = Vector3D(maximumPoint.x, maximumPoint.y, minimumPoint.z);
	points[7] = Vector3D(maximumPoint);

	Vector3D rotatedPoint = (Vector3D::toQuaternion(points[0]) * rotation).toEulerAngles();
	minimumPoint = rotatedPoint;
	maximumPoint = rotatedPoint;

	for (size_t i = 1; i < points.size(); i++){
		rotatedPoint = (Vector3D::toQuaternion(points[i]) * rotation).toEulerAngles();
		updatePoints(rotatedPoint);
	}
}

/**********************************************************************
	contains

	点を含んでいるか判定する
**********************************************************************/
bool AxisAlignedBoundingBox::contains(const Vector3D& point) const{
	return
		minimumPoint.x < point.x &&
		minimumPoint.y < point.y &&
		minimumPoint.z < point.z &&
		point.x < maximumPoint.x &&
		point.y < maximumPoint.y &&
		point.z < maximumPoint.z;
}

/**********************************************************************
	getSquaredDistance

	点との距離を取得する
**********************************************************************/
float AxisAlignedBoundingBox::getSquaredDistance(const Vector3D& point) const{
	float dx = Math::getMaximum(minimumPoint.x - point.x, 0.0f);
	dx = Math::getMaximum(dx, point.x - maximumPoint.x);

	float dy = Math::getMaximum(minimumPoint.y - point.y, 0.0f);
	dy = Math::getMaximum(dy, point.y - maximumPoint.y);

	float dz = Math::getMaximum(minimumPoint.z - point.z, 0.0f);
	dz = Math::getMaximum(dy, point.z - maximumPoint.z);

	return dx * dx + dy * dy + dz * dz;
}

/**********************************************************************
	intersect

	交差判定を行う
**********************************************************************/
bool intersect(const LineSegment& lineSegment, const Plane& plane, float& t_out){
	float denominator = Vector3D::getInnerProduct(lineSegment.end - lineSegment.start, plane.normal);

	if(Math::areApproximate(denominator, 0.0f)){
		if(Math::areApproximate(Vector3D::getInnerProduct(lineSegment.start, plane.normal) - plane.signedMinimalDistance, 0.0f)){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		float numerator = -Vector3D::getInnerProduct(lineSegment.start, plane.normal) - plane.signedMinimalDistance;
		t_out = numerator / denominator;

		if(0.0f <= t_out && t_out <= 1.0f){
			return true;
		}
		else{
			return false;
		}
	}
}
bool intersect(const LineSegment& lineSegment, const Sphere& sphere, float& t_out){
	Vector3D x = lineSegment.start - sphere.center;
	Vector3D y = lineSegment.end - lineSegment.start;
	float a = Vector3D::getInnerProduct(y, y);
	float b = 2.0f * Vector3D::getInnerProduct(x, y);
	float c = Vector3D::getInnerProduct(x, x) - sphere.radius * sphere.radius;

	float discriminant = b * b - 4.0f * a * c;
	if(discriminant < 0.0f){
		return false;
	}
	else{
		discriminant = Math::getSquareRoot(discriminant);
		float tMin = (-b - discriminant) / (2.0f * a);
		float tMax = (-b + discriminant) / (2.0f * a);

		if(0.0f <= tMin && tMin <= 1.0f){
			t_out = tMin;
			return true;
		}
		else if (0.0f <= tMax && tMax <= 1.0f){
			t_out = tMax;
			return true;
		}
		else{
			return false;
		}
	}
}
bool intersect(const LineSegment& lineSegment, const AxisAlignedBoundingBox& boundingBox, float& t_out, Vector3D& normal_out){
	std::vector<std::pair<float, Vector3D>> tValues;

	testSidePlane(lineSegment.start.x, lineSegment.end.x, boundingBox.minimumPoint.x, Vector3D::left, tValues);
	testSidePlane(lineSegment.start.x, lineSegment.end.x, boundingBox.maximumPoint.x, Vector3D::right, tValues);
	testSidePlane(lineSegment.start.y, lineSegment.end.y, boundingBox.minimumPoint.y, Vector3D::down, tValues);
	testSidePlane(lineSegment.start.y, lineSegment.end.y, boundingBox.maximumPoint.y, Vector3D::up, tValues);
	testSidePlane(lineSegment.start.z, lineSegment.end.z, boundingBox.minimumPoint.z, Vector3D::back, tValues);
	testSidePlane(lineSegment.start.z, lineSegment.end.z, boundingBox.maximumPoint.z, Vector3D::forward, tValues);

	std::sort(tValues.begin(), tValues.end(), [](const std::pair<float, Vector3D>& a, const std::pair<float, Vector3D>& b){return a.first < b.first;});

	Vector3D point;
	for(auto& t : tValues){
		point = lineSegment.getPoint(t.first);

		if(boundingBox.contains(point)){
			t_out = t.first;
			normal_out = t.second;

			return true;
		}
	}

	return false;
}
bool intersect(const Sphere& a, const Sphere& b){
	return (a.center - b.center).getSquaredMagnitude() <= (a.radius + b.radius) * (a.radius + b.radius);
}
bool intersect(const AxisAlignedBoundingBox& a, const AxisAlignedBoundingBox& b){
	return
		b.minimumPoint.x < a.maximumPoint.x &&
		b.minimumPoint.y < a.maximumPoint.y &&
		b.minimumPoint.z < a.maximumPoint.z &&
		a.minimumPoint.x < b.maximumPoint.x &&
		a.minimumPoint.y < b.maximumPoint.y &&
		a.minimumPoint.z < b.maximumPoint.z;
}
bool intersect(const Sphere& sphere, const AxisAlignedBoundingBox& boundingBox){
	return boundingBox.getSquaredDistance(sphere.center) <= (sphere.radius * sphere.radius);
}

/**********************************************************************
	testSidePlane

	側面の交差判定を行う
**********************************************************************/
bool testSidePlane(float start, float end, float negativeD, const Vector3D& normal, std::vector<std::pair<float, Vector3D>>& out){
	float denominator = end - start;
	
	if(Math::areApproximate(denominator, 0.0f)){
		return false;
	}
	else{
		float numerator = -start + negativeD;
		float t = numerator / denominator;

		if(0.0f <= t && t <= 1.0f){
			out.emplace_back(t, normal);
			return true;
		}
		else{
			return false;
		}
	}
}

bool SweptSphere(const Sphere& P0, const Sphere& P1, const Sphere& Q0, const Sphere& Q1, float& t){
	return false;
}
