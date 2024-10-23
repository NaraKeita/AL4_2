#include "MathUtilityForText.h"
#include <cmath>
#include <numbers>
#include <assert.h>
#include <math\MathUtility.h>
using namespace MathUtility;
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate) {
    //回転
	Matrix4x4 rotate = MakeRotateXMatrix(rot.x) * MakeRotateYMatrix(rot.y);
	rotate = rotate * MakeRotateZMatrix(rot.z);

    Matrix4x4 affin = {
	    scale.x * rotate.m[0][0],
	    scale.x * rotate.m[0][1],
	    scale.x * rotate.m[0][2],
	    0.0f,
	    scale.y * rotate.m[1][0],
	    scale.y * rotate.m[1][1],
	    scale.y * rotate.m[1][2],
	    0.0f,
	    scale.z * rotate.m[2][0],
	    scale.z * rotate.m[2][1],
	    scale.z * rotate.m[2][2],
	    0.0f,
	    translate.x,
	    translate.y,
	    translate.z,
	    1.0f};

	return affin;
}

float EaseInOut(float x1, float x2, float t) {
	float easedT = -(std::cosf(std::numbers::pi_v<float> * t) - 1.0f) / 2.0f;
    return Lerp(x1,x2,easedT);
}


Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) {
    return Vector3(Lerp(v1.x, v2.x, t), Lerp(v1.y, v2.y, t), Lerp(v1.z, v2.z, t));
}


bool IsCollision(const AABB& aabb1, const AABB& aabb2) {
	return (aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
           (aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
           (aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z);
}