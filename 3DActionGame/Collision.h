//======================================================================
//
//	Collision
//
//	各種コリジョンクラスの規定と判定関数を持つクラス
//
//======================================================================

#pragma once

#include <vector>
#include "Math.h"

class LineSegment{
	public:
		Vector3D start;
		Vector3D end;

		LineSegment();
		LineSegment(const Vector3D& start, const Vector3D& end);

		Vector3D getPoint(float t) const;
		float getMinimumSquaredDistance(const Vector3D& point) const;
		static float getMinimumSquaredDistance(const LineSegment& lineSegmentA, const LineSegment& lineSegmentB);
};

class Plane{
	public:
		Vector3D normal;
		float signedMinimalDistance;

		Plane();
		Plane(const Vector3D& normal, float signedMinimalDistance);
		Plane(const Vector3D& a, const Vector3D& b, const Vector3D& c);

		float getSignedDistance(const Vector3D& point) const;
};

class Sphere{
	public:
		Vector3D center;
		float radius;

		Sphere();
		Sphere(const Vector3D& center, float radius);

		bool contains(const Vector3D& point) const;
};

class AxisAlignedBoundingBox{
	public:
		Vector3D minimumPoint;
		Vector3D maximumPoint;

		AxisAlignedBoundingBox();
		AxisAlignedBoundingBox(const Vector3D& minimumPoint, const Vector3D& maximumPoint);

		void updatePoints(const Vector3D& point);
		void rotate(const Quaternion& rotation);
		bool contains(const Vector3D& point) const;
		float getSquaredDistance(const Vector3D& point) const;
};

class CollisionInformation{
	public:
		Vector3D point;
		Vector3D normal;

		class Actor* actor;
		class BoxColliderComponent* collider;
};

bool intersect(const LineSegment& lineSegment, const Plane& plane, float& outT);
bool intersect(const LineSegment& lineSegment, const Sphere& sphere, float& t_out);
bool intersect(const LineSegment& lineSegment, const AxisAlignedBoundingBox& boundingBox, float& t_out, Vector3D& normal_out);
bool intersect(const Sphere& a, const Sphere& b);
bool intersect(const AxisAlignedBoundingBox& a, const AxisAlignedBoundingBox& b);
bool intersect(const Sphere& sphere, const AxisAlignedBoundingBox& boundingBox);

bool testSidePlane(float start, float end, float negativeD, const Vector3D& normal, std::vector<std::pair<float, Vector3D>>& out);

bool SweptSphere(const Sphere& P0, const Sphere& P1, const Sphere& Q0, const Sphere& Q1, float& t);
