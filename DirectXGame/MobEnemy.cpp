#include "MobEnemy.h"
#include<cassert>
#include"MathUtilityForText.h"
#include "Player.h"

MobEnemy::~MobEnemy() { delete bullet_; }

void MobEnemy::Initialize(Model* model/*, uint32_t textureHandle*/, Vector3 pos_) {
	// ワールド変換の初期化
	worldTransform_.Initialize();
	// NULLポインタをチェックする
	assert(model);
	// シングルインスタンスを取得する
	// input_ = Input::GetInstance();
	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	//textureHandle_ = textureHandle;

	worldTransform_.translation_ = pos_;

	// ワールド変換の初期化
	worldTransform_.Initialize();

	flag = 0;
	timer_ = 0.0f;
}

void MobEnemy::Update() {
	// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
	if (worldTransform_.translation_.z)
		// worldTransform_.translation_.z -= 0.1f;
		// worldTransform_.rotation_.x -= 0.1f;

		// 移動

		//switch (phase_) {
		//case Phase::Approach:
		//default:
		//	// 接近フェーズの更新関数
		//	// 移動（ベクトルを加算）
		//	// worldTransform_.translation_.z -= 0.1f;
		//	// 既定の位置に到達したら離脱
		//	if (worldTransform_.translation_.z < 0.0f) {
		//		phase_ = Phase::Leave;
		//	}
		//	break;
		//case Phase::Leave:
		//	// 離脱フェーズの更新関数
		//	// 移動
		//	worldTransform_.translation_.x += 0.1f;
		//	worldTransform_.translation_.y += 0.1f;

		//	break;
		//}

		bullets_.remove_if([](EnemyBullet* bullet) {
			if (bullet->IsDead()) {
				delete bullet;
				return true;
			}
			return false;
		});

	// キャラクター攻撃処理
	Attack();

	// 弾更新
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
}

void MobEnemy::Draw(Camera& camera) {
	// modelの描画
	if (Life == true) {
		model_->Draw(worldTransform_, camera);
	}

	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(camera);
	}
}

void MobEnemy::Approach() {
	//発射タイマーを初期化	
    firingTimer_ = kFireInterval;
}


void MobEnemy::Fire() {
	assert(player_);
	// 弾の速さ（調整項目）
	const float kBulletSpeed = 0.1f;
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

	// 弾を生成し、初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	// 弾を登録する
	bullets_.push_back(newBullet);
}

void MobEnemy::Attack() {
	timer_++;
	if (timer_ >= 70.0f) {
		flag = 1;
	} else {
		flag = 0;
	}
	if (flag == 1) {
		if (bullet_) {
			delete bullet_;
			bullet_ = nullptr;
		}
		if (isDead_ == false) {
			Fire();
		}

		timer_ = 0.0f;
	}
}

void MobEnemy::OnCollision(const Player* player) {
		(void)player;
		isDead_ = true;
		isFinished_ = true;
		Life = false;
	}

Vector3 MobEnemy::GetWorldPosition() {
	    Vector3 worldPos;
	    worldPos.x = worldTransform_.matWorld_.m[3][0];
	    worldPos.y = worldTransform_.matWorld_.m[3][1];
	    worldPos.z = worldTransform_.matWorld_.m[3][2];
	    return worldPos;
    }
