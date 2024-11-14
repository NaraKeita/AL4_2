#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include <array>
#include <numbers>
#include <math\MathUtility.h>
using namespace MathUtility;

class DeathParticles {
public:
	void Initialize(Model* model, Camera* camera, const Vector3& position);
	void Update();
	void Draw();

private:
	//パーティクルの個数
	static inline const uint32_t kNumParticles = 8;
	//ワールド変換データ
	std::array<WorldTransform, kNumParticles> worldTransforms_;

	//モデル
	Model* model_ = nullptr;
	Camera* camera_ = nullptr;

	//存続時間（消滅までの時間）<秒>
	static inline const float kDuration = 1;
	//移動の速さ
	static inline const float kSpeed = 0.1f;
	//分割した1個分の角度
	static inline const float kAngleUnit = 2 * std::numbers::pi_v<float> / kNumParticles;

	//終了フラグ
	bool isFinished_ = false;
	//経過時間カウント
	float counter_ = 0.0f;

	//色変更オブジェクト
	ObjectColor objectColor_;
	//色の数値
	Vector4 color_;
};
