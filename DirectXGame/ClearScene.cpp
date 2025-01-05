#include "ClearScene.h"
#include <numbers>

ClearScene::ClearScene() {}

ClearScene::~ClearScene() { delete modelFont_; }

void ClearScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ビュープロジェクション
	camera_.Initialize();

	modelFont_ = Model::CreateFromOBJ("clearFont");

	worldTransformFont_.Initialize();

	worldTransformFont_.translation_.y = 10;
	worldTransformFont_.scale_ = {2, 2, 2};

	//// サウンドデータの読み込み
	//soundDataHandle_ = audio_->LoadWave("Clear.wav");
	//// 音声再生
	//audio_->PauseWave(soundDataHandle_);
	//// 第2引数でループ再生を指定
	//voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);
}

void ClearScene::Update() {
	if (Input::GetInstance()->/*ReleseKey*/ TriggerKey(DIK_RETURN)) {
		// 音声停止
		audio_->StopWave(voiceHandle_);
		finished_ = true;
	}
	// タイマーを加算
	timer_ += 1.0f / 60.0f;

	// 行列を更新
	worldTransformFont_.UpdateMatrix();
}

void ClearScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	// ここに3Dオブジェクトの描画処理を追加できる
	modelFont_->Draw(worldTransformFont_, camera_);

	// 3Dオブジェクト描画処理後
	Model::PostDraw();
}
