#include "Enemy.h"
#include<cassert>
#include"MathUtilityForText.h"

Enemy::~Enemy() { delete bullet_; }

void Enemy::Initialize(Model* model, uint32_t textureHandle) {
	// NULLポインタをチェックする
	assert(model);
	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.translation_ = {2, 2, 20};
	
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

	//移動

	switch (phase_) {
	case Phase::Approach:
	default:
		//接近フェーズの更新関数
		//移動（ベクトルを加算）
		worldTransform_.translation_.z -= 0.1f;
		//既定の位置に到達したら離脱
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave:
		//離脱フェーズの更新関数
		//移動
		worldTransform_.translation_.x += 0.1f;
		worldTransform_.translation_.y += 0.1f;

		break;
	
	}
	// 弾更新
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
}

void Enemy::Draw(Camera& camera) {
	// modelの描画
	model_->Draw(worldTransform_, camera, textureHandle_);
	// 描画
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(camera);
	}
}

void Enemy::Fire() {
	
}
