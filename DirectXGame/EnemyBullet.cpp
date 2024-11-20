#include "EnemyBullet.h"
#include <cassert>
#include "MathUtilityForText.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("black1x1.png");
	worldTransform_.Initialize();

	// ワールドトランスフォームの初期化
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	// ワールド変換の初期化
	worldTransform_.Initialize();

	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
}

void EnemyBullet::Update() {

	worldTransform_.translation_ += velocity_;

	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();

	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	worldTransform_.UpdateMatrix();	

	// 座標を移動させる（1フレーム分の移動量を足しこむ）
	worldTransform_.translation_ -= velocity_;
	worldTransform_.rotation_.z += 0.1f;
}

void EnemyBullet::Draw(const Camera& camera) {
	// modelの描画
	model_->Draw(worldTransform_, camera, textureHandle_);
}
