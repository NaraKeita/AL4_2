#include "PlayerBullet.h"
#include<cassert>
#include "MathUtilityForText.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	//NULLポインタチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("black1x1.png");
	worldTransform_.Initialize();

	//ワールドトランスフォームの初期化
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	// ワールド変換の初期化
	worldTransform_.Initialize();

	//引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;

}

void PlayerBullet::Update() { 
	//ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();

	//座標を移動させる（1フレーム分の移動量を足しこむ）
	worldTransform_.translation_ += velocity_;
	worldTransform_.rotation_.z += 0.2f;
}

void PlayerBullet::Draw(const Camera& camera) {
	//modelの描画
	model_->Draw(worldTransform_, camera, textureHandle_);
}


void PlayerBullet::Hit() {

}

void PlayerBullet::OnCollision() { 
	isDead_ = true;

}

Vector3 PlayerBullet::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}
