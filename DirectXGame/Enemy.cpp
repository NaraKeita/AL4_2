#include "Enemy.h"
#include<cassert>
#include"MathUtilityForText.h"
#include "Player.h"

Enemy::~Enemy() {
	for (EnemyBullet* bullet : bullets_) {
	    delete bullet;
	}

}

void Enemy::Initialize(Model* model, uint32_t textureHandle) {
	// NULLポインタをチェックする
	assert(model);
	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.translation_ = {2, 2, 20};
	
	// 引数で受け取った初期座標をセット
	


	// ワールド変換の初期化
	worldTransform_.Initialize();

	flag = 0;
	timer = 0.0f;

	//接近フェーズ初期化
	Approach();

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

	// キャラクター攻撃処理
	Attack();

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

void Enemy::Approach() {
    //発射タイマーを初期化
	firingTimer_ = kFireInterval;

	//接近タイマーカウントダウン


}

void Enemy::Fire() { 
	assert(player_);

	//弾の速さ（調整項目）
	const float kBulletSpeed = 0.5f;

	// 自キャラのワールド座標を取得する
	Vector3 targetPos = player_->GetWorldPosition();
	// 敵キャラのワールド座標を取得する
	Vector3 basePos = this->GetWorldPosition();
	// 敵キャラ→自キャラの差分ベクトル
	Vector3 velocity = targetPos - basePos;
	// ベクトルの正規化
	velocity = Normalize(velocity);
	// ベクトルの長さを、早さに合わせる
	velocity *= kBulletSpeed;

	//弾を生成し、初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity_);

	//弾を登録する
	bullets_.push_back(newBullet);

}

void Enemy::Attack() {
	timer++;
	if (timer >= 50.0f) {
		flag = 1;
	} else {
		flag = 0;
	}

	if (flag == 1) {
		if (bullet_) {
			delete bullet_;
			bullet_ = nullptr;
		}

		// 弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		// 弾を生成し、初期化
		EnemyBullet* newBullet = new EnemyBullet();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);

		// 弾を登録する
		bullets_.push_back(newBullet);
		timer = 0.0f;

	}
}
