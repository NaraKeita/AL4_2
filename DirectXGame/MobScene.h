//#pragma once
//#include <KamataEngine.h>
//using namespace KamataEngine;
//#include "Player.h"
//#include "PlayerBullet.h"
////#include"MobEnemy.h"
//#include "Enemy.h"
////#include "DeathParticles.h"
//#include "scene/GameScene.h"
//
//
//class MobScene {
//public: // メンバ関数
//	/// <summary>
//	/// コンストクラタ
//	/// </summary>
//	MobScene();
//
//	/// <summary>
//	/// デストラクタ
//	/// </summary>
//	~MobScene();
//
//	/// <summary>
//	/// 初期化
//	/// </summary>
//	void Initialize();
//
//	int HP;
//
//	/// <summary>
//	/// 毎フレーム処理
//	/// </summary>
//	void Update();
//
//	/// <summary>
//	/// 描画
//	/// </summary>
//	void Draw();
//	bool isDebugCameraActive_ = false;
//
//	// デスフラグのgetter
//	bool PlayerIsFinished() const { return PlayerFinished_; }
//	bool EnemyIsFinished() const { return EnemyFinished_; }
//
//private: // メンバ変数
//	// 終了フラグ
//	bool PlayerFinished_ = false;
//
//	bool EnemyFinished_ = false;
//
//	DirectXCommon* dxCommon_ = nullptr;
//	Input* input_ = nullptr;
//	Audio* audio_ = nullptr;
//
//	GameScene gameScene_;
//
//	// 自キャラ
//	Player* player_ = nullptr;
//	// 弾
//	PlayerBullet* playerBullet_ = nullptr;
//	// 弾
//	EnemyBullet* enemyBullet_ = nullptr;
//	// 敵
//	Enemy* enemy_ = nullptr;
//	// モブ敵
//	//MobEnemy* mobEnemy_n[4] = {nullptr};
//	// プレイヤーのモデル
//	Model* model_ = nullptr;
//
//	Model* mobModel_ = nullptr;
//
//	// テクスチャハンドル
//	//uint32_t textureHandle_ = 0;
//	uint32_t bulletText_ = 0;
//	uint32_t enemyText_ = 0;
//	WorldTransform worldTransform_;
//	// ビュープロジェクション
//	Camera viewProjection_;
//	// デバッグカメラ
//	DebugCamera* debugCamera_ = nullptr;
//
//	// パーティクル
//	//DeathParticles* deathParticles_ = nullptr;
//	Model* modelDeathParticle_ = nullptr;
//
//	// UI
//	uint32_t playerLifeTexture3_ = 0;
//	uint32_t playerLifeTexture2_ = 0;
//	uint32_t playerLifeTexture1_ = 0;
//	uint32_t playerLifeTexture0_ = 0;
//	Sprite* sprite3_ = nullptr;
//	Sprite* sprite2_ = nullptr;
//	Sprite* sprite1_ = nullptr;
//	Sprite* sprite0_ = nullptr;
//
//	// 弾
//	// PlayerBullet* bullet_ = nullptr;
//
//	//std::list<DeathParticles*> deathPartiy_;
//
//	// サウドデータハンドル
//	uint32_t soundDataHandle_ = 0;
//	// 音声再生ハンドル
//	uint32_t voiceHandle_ = 0;
//
//	/// <summary>
//	/// ゲームシーン用
//	/// </summary>
//};
