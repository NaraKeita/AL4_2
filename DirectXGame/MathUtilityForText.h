#pragma once

#include<math.h>
#include"math\Matrix4x4.h"
#include"math\Vector3.h"
#include "AABB.h"
using namespace KamataEngine;

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate);

float EaseInOut(float x1, float x2, float t);
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);

bool IsCollision(const AABB& aabb1, const AABB& aabb2);
