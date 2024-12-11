#pragma once
#include "EnemyBullet.h"
#include "MathUtilityForText.h"
#include <KamataEngine.h>
using namespace KamataEngine;

//自機クラスの前方宣言
class Player;

//行動フェーズ
enum class Phase { 
	Approach,  //接近する
    Leave,     //離脱する
};

class Enemy {
public:
	~Enemy();
	// キーボード入力
	Input* input_ = nullptr;

	void Initialize(Model* model, uint32_t textureHandle);

	void Update();

	void Draw(Camera& viewProjection);

	void Approach();
	/*void MoveApproach();
	void MoveLeave();*/

	//弾の発射に使う
	void Fire();
	void Attack();

	Vector3 GetPosition() { return worldTransform_.translation_; }

	void SetPlayer(Player* player) { player_ = player; }

	std::list<EnemyBullet*> bullets_;
	std::list<EnemyBullet*> GetBullet() { return bullets_; }
	//発射間隔
	static const int kFireInterval = 60;

	// 衝突応答
	void OnCollision(const Player* player);

	//ワールド座標を取得
	Vector3 GetWorldPosition();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Vector3 velocity_ = {0, 0, -0.1f};
	
	Vector3 velocityLeave_ = {-0.3f, 0.3f, -0.1f};

	// 弾
	EnemyBullet* bullet_ = nullptr;
	//フェーズ
	Phase phase_ = Phase::Approach;
	//発射タイマー
	int32_t firingTimer_ = 0;
	// 自キャラ
	Player* player_ = nullptr;
	
	int shotCoolTimer;
	static inline const int kShotCoolTimer = 50;

};
