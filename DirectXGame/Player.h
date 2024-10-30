#pragma once
#include "PlayerBullet.h"
#include <KamataEngine.h>
using namespace KamataEngine;

class Player {
public:
	// キーボード入力
	Input* input_ = nullptr;

	void Initialize(Model* model, uint32_t textureHandle/*, ViewProjection* viewProjection*/);

	void Update();
	void Draw(Camera& viewProjection);
	void Rotate();
	void Attack();
	

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// ImGuiで値を入力する変数
	float inputFloat3[3] = {0, 0, 0};
	// 弾
	PlayerBullet* bullet_ = nullptr;
	
};
