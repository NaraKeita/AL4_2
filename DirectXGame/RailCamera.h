#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

class RailCamera {
public:
	
	void Initialize(const Vector3& position,  Camera* camera, const Vector3& rotate);
	void Update();
	
private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	//ビュープロジェクション
	Camera* camera_ = nullptr;
};
