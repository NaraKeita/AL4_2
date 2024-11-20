#pragma once
#include <KamataEngine.h>
#include <MathUtilityForText.h>
using namespace KamataEngine;

class EnemyBullet {
public:
	/// 初期化
	/// </summary>
	/// <param name="model>モデル</param>
	/// <param name="textureHandle>テクスチャハンドル</param>
	void Initialize(Model* model, const Vector3& positon, const Vector3& velocity);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera>camera(参照渡し)</param>
	void Draw(const Camera& camera);

	Vector3 velocity_;

	void Hit();

	static const int32_t kLifeTime = 60 * 5;	
	int32_t deathTimer_ = kLifeTime;	
	Vector3 GetPosition() { return worldTransform_.translation_; }
	bool isDead_ = false;
	bool IsDead() const { return isDead_; }
	void OnCollision();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//bool isDead_ = false;
};
