#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

class Enemy {
public:
	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(Camera& viewProjection);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;




};
