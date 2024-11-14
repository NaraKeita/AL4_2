#pragma once
#include "EnemyBullet.h"
#include <KamataEngine.h>
using namespace KamataEngine;

class Player;

//行動フェーズ
enum class Phase { 
	Approach,  //接近する
    Leave,     //離脱する
};

class Enemy {
public:
	~Enemy();
	void Initialize(Model* model, uint32_t textureHandle);
	void Update();
	void Draw(Camera& viewProjection);
	/*void MoveApproach();
	void MoveLeave();*/
	//弾の発射に使う
	void Fire();
	Vector3 GetPosition() { return worldTransform_.translation_; }
	std::list<EnemyBullet*> bullets_;
	// 衝突応答
	void OnCollision(const Player* player);

	bool IsFinished() { return finished_; }

	// デスフラグ
	bool isDead_ = false;
	// デスフラグのgetter
	bool IsDead() const { return isDead_; }

private:
	// 終了フラグ
	bool finished_ = false;

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
	//命
	bool Life = true;

	//フェーズ
	Phase phase_ = Phase::Approach;
	
};
