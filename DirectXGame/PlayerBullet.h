#pragma once
#include <MathUtilityForText.h>
#include <KamataEngine.h>
using namespace KamataEngine;

class PlayerBullet {
public:
	/// 初期化
	/// </summary>
	/// <param name="model>モデル</param>
	/// <param name="textureHandle>テクスチャハンドル</param>
	void Initialize(Model* model, const Vector3& pos, const Vector3 velocity);

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

	void OnCollision();
	bool isDead_ = false; 

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

};
