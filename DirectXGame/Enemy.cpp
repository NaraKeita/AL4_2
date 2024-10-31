#include "Enemy.h"

void Enemy::Initialize(Model* model, uint32_t textureHandle) {
	// NULLポインタをチェックする
	assert(model);
	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;
	
	// 引数で受け取った初期座標をセット
	//worldTransform_.translation_ = pos;
	// ワールド変換の初期化
	worldTransform_.Initialize();
}

void Enemy::Update() {
	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
	
	worldTransform_.translation_.z -= 0.1f;
	//worldTransform_.rotation_.x -= 0.1f;
}

void Enemy::Draw(Camera& camera) {
	// modelの描画
	model_->Draw(worldTransform_, camera, textureHandle_);
}
