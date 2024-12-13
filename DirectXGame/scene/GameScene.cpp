#include <KamataEngine.h>
using namespace KamataEngine;
#include "GameScene.h"
#include <cassert>


GameScene::GameScene() { 
	
}

GameScene::~GameScene() {
	// 自キャラの開放
	delete model_;
	delete player_;
	delete debugCamera_;
	delete enemy_;
	delete modelSkydome_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");
	bulletText_ = TextureManager::Load("black1x1.png");

	//
	model_ = Model::Create();
	//
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	skydome_->Initialize(modelSkydome_, &viewProjection_);

	//skydomeの生成
	skydome_ = new Skydome();
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_/*, &viewProjection_*/);
	//敵の生成
	enemy_ = new Enemy();

	//Vector3 enemyPosition(30, 2.0f, 50.0f);

	//敵の初期化
	enemy_->Initialize(model_, textureHandle_);
	const uint32_t kNumBlockVirtical = 20;
	const uint32_t kNumBlockHorizontal = 100;

	// 敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);

	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(kNumBlockHorizontal, kNumBlockVirtical);

	//軸方向
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetCamera(&viewProjection_);


}

void GameScene::Update() {
	player_->Update();
	debugCamera_->Update();
	enemy_->Update();

	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
	#endif

	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetCamera().matView;
		viewProjection_.matProjection = debugCamera_->GetCamera().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.UpdateMatrix();
	}

	// 自機の弾が敵に当たったとき
	std::list<PlayerBullet*> playerBullets = player_->GetBullet();
	for (PlayerBullet* playerBullet : playerBullets) {
		Vector3 enemyPosition = enemy_->GetPosition();
		Vector3 playerBulletPosition = playerBullet->GetPosition();
		if (abs(playerBulletPosition.x - enemyPosition.x) < 3 && abs(playerBulletPosition.y - enemyPosition.y) < 3 && abs(playerBulletPosition.z - enemyPosition.z) < 3) {
			playerBullet->OnCollision();
			enemy_->OnCollision(player_);
		}
	}

	// 敵の弾が自機に当たったとき
	std::list<EnemyBullet*> enemyBullets = enemy_->GetBullet();
	for (EnemyBullet* enemyBullet : enemyBullets) {
		Vector3 playerPosition = player_->GetPosition();
		Vector3 enemyBulletPosition = enemyBullet->GetPosition();
		if (abs(enemyBulletPosition.x - playerPosition.x) < 3 && abs(enemyBulletPosition.y - playerPosition.y) < 3 && abs(enemyBulletPosition.z - playerPosition.z) < 3) {
			// enemy_->OnCollision(player_);
			enemyBullet->OnCollision();
			player_->OnCollision(enemy_);
		}
	}

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	// 自キャラの描画
	player_->Draw(viewProjection_);
	//敵の描画
	enemy_->Draw(viewProjection_);
	//skydome
	skydome_->Draw();
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
