#include "PlayerBullet.h"
//#include "TextureManager.h"
#include<cassert>


void PlayerBullet::Initialize(Model* model, const Vector3& position) {
	//NULLポインタチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("black1x1.png");

	//ワールドトランスフォームの初期化
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update() { 
	//ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

void PlayerBullet::Draw(const Camera& camera) {
	//modelの描画
	model_->Draw(worldTransform_, camera, textureHandle_);
}
