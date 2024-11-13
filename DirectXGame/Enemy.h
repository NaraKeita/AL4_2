#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

//行動フェーズ
enum class Phase { 
	Approach,  //接近する
    Leave,     //離脱する
};

class Enemy {
public:
	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(Camera& viewProjection);
	void MoveApproach();
	void MoveLeave();
	
private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Vector3 velocity_ = {0, 0, -0.1f};
	
	Vector3 velocityLeave_ = {-0.3f, 0.3f, -0.1f};

	//フェーズ
	Phase phase_ = Phase::Approach;
	
};
