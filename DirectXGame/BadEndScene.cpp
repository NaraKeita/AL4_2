#include "BadEndScene.h"

BadEndScene::BadEndScene() {}

BadEndScene::~BadEndScene() {
	delete modelFont_;
	finished_ = false;
}

void BadEndScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ビュープロジェクション
	camera_.Initialize();

	modelFont_ = Model::CreateFromOBJ("badEndFont");
	
	worldTransformFont_.Initialize();
	worldTransform_.Initialize();

	worldTransformFont_.translation_.y = 10;
	worldTransformFont_.scale_ = {1, 1, 1};

}

void BadEndScene::Update() {
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		finished_ = true;
	}
	// 行列を更新
	worldTransformFont_.UpdateMatrix();
}

void BadEndScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	// ここに3Dオブジェクトの描画処理を追加できる
	modelFont_->Draw(worldTransformFont_, camera_);
	// modelPlayer_->Draw(worldTransform_, camera_);

	// 3Dオブジェクト描画処理後
	Model::PostDraw();
}
