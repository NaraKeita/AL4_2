#pragma once

#include <KamataEngine.h>
using namespace KamataEngine;
#include "Player.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	bool isDebugCameraActive_ = false;


private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	//自キャラ
	Player* player_ = nullptr;
	// プレイヤーのモデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	WorldTransform worldTransform_;
	// ビュープロジェクション
	Camera viewProjection_;
	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
