#pragma once
#include "EnemyBullet.h"
#include "MathUtilityForText.h"
#include <KamataEngine.h>
using namespace KamataEngine;

class Player; // 自機クラスの前方宣言

class MobEnemy {
public:
	~MobEnemy();
	void Initialize(Model* model, uint32_t textureHandle, Vector3 pos_);
	void Update();
	void Draw(Camera& camera);
	void Approach();

	// 弾の発射に使う
	void Fire();
	void Attack();

	Vector3 GetPosition() { return worldTransform_.translation_; }
	std::list<EnemyBullet*> bullets_;
	std::list<EnemyBullet*> GetBullet() { return bullets_; }
	// 発射間隔	// 衝突応答
	static const int kFireInterval = 60;

	int flag;
	float timer_;

	void OnCollision(const Player* player);

	// 衝突応答
	// void OnCollision(const Player* player);

	bool IsFinished() { return isFinished_; }

	// デスフラグ
	bool isDead_ = false;
	// デスフラグのgetter
	bool IsDead() const { return isDead_; }

	// 自キャラ
	Player* player_ = nullptr;
	void SetPlayer(Player* player) { player_ = player; }
	Vector3 GetWorldPosition();

	// キーボード入力	public:
	Input* input_ = nullptr;

private:
	// 終了フラグ
	bool isFinished_ = false;
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Vector3 velocityLeave_ = {-0.3f, 0.3f, -0.1f};

	// 弾
	EnemyBullet* bullet_ = nullptr;
	// 命
	bool Life = true;
	
	// 発射タイマー
	int32_t firingTimer_ = 0;
};
