#include "MobScene.h"


MobScene::MobScene() {}

MobScene::~MobScene() {
	// 自キャラの開放
	delete model_;
	delete player_;
	delete debugCamera_;
	for (int i = 0; i < 4; i++) {
		delete mobEnemy_n[i];
	}
	delete modelDeathParticle_;
}

void MobScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	// ファイル名を指定してテクスチャを読み込む
	//textureHandle_ = TextureManager::Load("mario.jpg");
	//bulletText_ = TextureManager::Load("black1x1.png");

	// モデル
	model_ = Model::CreateFromOBJ("player");
	mobModel_ = Model::CreateFromOBJ("mob");
	// ワールドトランスフォーム
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	// 自キャラの生成
	player_ = new Player();
	// 自キャラの初期化

	player_->Initialize(model_, worldTransform_.translation_);

	
	HP = 3;
	
	// モブ敵の生成
	for (int i = 0; i < 4; i++) {
		mobEnemy_n[i] = new MobEnemy();
	}
	// モブ敵の初期化
	mobEnemy_n[0]->Initialize(mobModel_, {30, -20, 20});
	mobEnemy_n[1]->Initialize(mobModel_, {-30, -20, 20});
	mobEnemy_n[2]->Initialize(mobModel_, {30, 14, 20});
	mobEnemy_n[3]->Initialize(mobModel_, {-30, 14, 20});

	const uint32_t kNumBlockVirtical = 20;
	const uint32_t kNumBlockHorizontal = 100;

	// 敵キャラに自キャラのアドレスを渡す
	for (int i = 0; i < 4; i++) {
		mobEnemy_n[i]->SetPlayer(player_);
	}

	modelDeathParticle_ = Model::CreateFromOBJ("DeathParticle", true);

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(kNumBlockHorizontal, kNumBlockVirtical);

	// 軸方向
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetCamera(&viewProjection_);

	// サウンドデータの読み込み
	soundDataHandle_ = audio_->LoadWave("Mob.wav");
	// 音声再生
	audio_->PauseWave(soundDataHandle_);
	// 第2引数でループ再生を指定
	voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);

	playerLifeTexture3_ = TextureManager::Load("playerLife/3.png");
	sprite3_ = Sprite::Create(playerLifeTexture3_, {0, 0});

	playerLifeTexture2_ = TextureManager::Load("playerLife/2.png");
	sprite2_ = Sprite::Create(playerLifeTexture2_, {0, 0});

	playerLifeTexture1_ = TextureManager::Load("playerLife/1.png");
	sprite1_ = Sprite::Create(playerLifeTexture1_, {0, 0});

	playerLifeTexture0_ = TextureManager::Load("playerLife/0.png");
	sprite0_ = Sprite::Create(playerLifeTexture0_, {0, 0});

}

void MobScene::Update() {
	player_->Update();
	debugCamera_->Update();
	for (int i = 0; i < 4; i++) {
		mobEnemy_n[i]->Update();
	}

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
		for (int i = 0; i < 4; i++) {
			if (mobEnemy_n[i]->IsDead() == false) {

				Vector3 enemyPosition = mobEnemy_n[i]->GetPosition();
				Vector3 playerBulletPosition = playerBullet->GetPosition();
				if (abs(playerBulletPosition.x - enemyPosition.x) < 3 && abs(playerBulletPosition.y - enemyPosition.y) < 3 && abs(playerBulletPosition.z - enemyPosition.z) < 3) {
					// player_->OnCollision(enemy_);
					playerBullet->OnCollision();
					mobEnemy_n[i]->OnCollision(player_);
					// 仮の生成処理。後で消す
					deathParticles_ = new DeathParticles;
					deathParticles_->Initialize(modelDeathParticle_, &viewProjection_, worldTransform_.translation_);
				}
			}
		}
	}

	// 敵の弾が自機に当たったとき
	for (int i = 0; i < 4; i++) {
		std::list<EnemyBullet*> enemyBullets = mobEnemy_n[i]->GetBullet();

		for (EnemyBullet* enemyBullet : enemyBullets) {
			Vector3 playerPosition = player_->GetPosition();
			Vector3 enemyBulletPosition = enemyBullet->GetPosition();
			if (abs(enemyBulletPosition.x - playerPosition.x) < 3 && abs(enemyBulletPosition.y - playerPosition.y) < 3 && abs(enemyBulletPosition.z - playerPosition.z) < 3) {
				enemyBullet->OnCollision();
				//player_->OnCollision(mobEnemy_n[i]);
				HP -= 1;
				// 仮の生成処理。後で消す
				/*deathParticles_ = new DeathParticles;
				deathParticles_->Initialize(modelDeathParticle_, &viewProjection_, worldTransform_.translation_);*/
			}
		}
	}

	// パーティクルの更新
	if (deathParticles_) {
		deathParticles_->Update();
	}

	//敵を倒したらClearSceneに行く為のフラグ
	int Dead = 0;
	for (int i = 0; i < 4; i++) {
		if (mobEnemy_n[i]->IsFinished()) {
			Dead += 1;
			
		}
	}

	if (Dead == 4) {
		EnemyFinished_ = true;
	}

	//プレイヤーが倒れたらDeadSceneに行く為のフラグ
	if (player_->IsFinished()) {
		PlayerFinished_ = true;
	}

	if (HP <= 0 || EnemyFinished_ == true) {
		// 音声停止
		audio_->StopWave(voiceHandle_);
	}
}

void MobScene::Draw() {
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
	// 敵の描画
	for (int i = 0; i < 4; i++) {
		mobEnemy_n[i]->Draw(viewProjection_);
	}

	// パーティクルの描画
	if (deathParticles_) {
		deathParticles_->Draw();
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	
	if (HP == 3) {
		sprite3_->Draw();
	}

	if (HP == 2) {
		sprite2_->Draw();
	}

	if (HP == 1) {
		sprite1_->Draw();
	}

	if (HP <= 0) {
		sprite0_->Draw();
	}

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
