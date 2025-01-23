#pragma once

#include <KamataEngine.h>
using namespace KamataEngine;
#include "Player.h"
#include "PlayerBullet.h"
#include "Enemy.h"
#include "Skydome.h"
#include "RailCamera.h"

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

	//弾
	PlayerBullet* playerBullet_ = nullptr;
	EnemyBullet* enemyBullet_ = nullptr;

	//敵
	Enemy* enemy_ = nullptr;

	// プレイヤーのモデル
	Model* model_ = nullptr;

	Skydome* skydome_ = nullptr;

	//SkyDomeのモデル
	Model* modelSkydome_ = nullptr;

	//RailCamera
	RailCamera* railCamera_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	uint32_t bulletText_ = 0;
	uint32_t enemyText_ = 0;
	WorldTransform worldTransform_;

	// ビュープロジェクション
	Camera viewProjection_;

	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
