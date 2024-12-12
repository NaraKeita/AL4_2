#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
#include <vector>

class BadEndScene {
public:
	BadEndScene();
	~BadEndScene();

	/// <summary>
	/// 初期化
	/// <summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// <summary>
	void Update();

	/// <summary>
	/// 描画
	/// <summary>
	void Draw();

	// デスフラグのgetter
	bool IsFinished() const { return finished_; }

private:
	// 終了フラグ
	bool finished_ = false;
	Model* modelFont_ = nullptr;
	
	// ワールド変換データ
	WorldTransform worldTransform_;

	// ビュープロジェクション
	Camera camera_;

	WorldTransform worldTransformFont_;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
};
