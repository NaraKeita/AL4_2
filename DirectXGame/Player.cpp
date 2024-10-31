#include "Player.h"
#include<cassert>
#include"MathUtilityForText.h"

void Player::Initialize(Model* model, uint32_t textureHandle/*, ViewProjection* viewProjection*/) {
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	//NULLポインタをチェックする
	assert(model);
	//引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;
	// ワールド変換の初期化
	worldTransform_.Initialize();
	
}

void Player::Update() {

	// 行列更新
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();

	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	//キャラクターの移動速さ
	const float kCharacterSpeed = 0.5f;

	//押した方向で移動ベクトルを変更（左右）
	if (input_->PushKey(DIK_LEFT) || input_->PushKey(DIK_A)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT) || input_->PushKey(DIK_D)) {
		move.x += kCharacterSpeed;
	}

	// 押した方向で移動ベクトルを変更（上下）
	if (input_->PushKey(DIK_DOWN) || input_->PushKey(DIK_S)) {
		move.y -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_UP) || input_->PushKey(DIK_W)) {
		move.y += kCharacterSpeed;
	}

	//座標移動（ベクトルの加算）
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;


	ImGui::Begin("Debug1");
	//flo
	ImGui::InputFloat3("InputFloat3", &worldTransform_.translation_.x);
	ImGui::SliderFloat3("SliderFloat3", &worldTransform_.translation_.x, -10.0f, 10.0f);
	ImGui::End();

	// 移動限界座標
	const float kMoveLimitX = 35;
	const float kMoveLimitY = 19;

	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	// キャラクター攻撃処理
	Attack();
	// 弾更新
	if (bullet_) {
		bullet_->Update();
	}

	worldTransform_.UpdateMatrix();

}

void Player::Draw(Camera& camera) {
	model_->Draw(worldTransform_, camera, textureHandle_);
	// 弾更新
	if (bullet_) {
		bullet_->Draw(camera);
	}
}

void Player::Rotate() {
	//-----------追加-------------//
	// 回転速さ[ラジアン/frame]
	const float kRotSpeed = 0.02f;

	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}

	//---------------------------//
}

void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);

		// 弾を登録する
		bullet_ = newBullet;
	}
}
