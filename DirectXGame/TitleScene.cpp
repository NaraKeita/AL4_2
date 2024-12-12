#include "TitleScene.h"
#include <numbers>


TitleScene::TitleScene() {}

TitleScene::~TitleScene() {
	delete modelFont_;
	finished_ = false;
}

void TitleScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ビュープロジェクション
	camera_.Initialize();

	modelFont_ = Model::CreateFromOBJ("titleFont");
	

	worldTransformFont_.Initialize();
	
}

void TitleScene::Update() {

		
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		    finished_ = true;
	}

	// 行列を更新
	worldTransformFont_.UpdateMatrix();
	//worldTransformPlayer_.UpdateMatrix();

	
}

void TitleScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	// ここに3Dオブジェクトの描画処理を追加できる
	modelFont_->Draw(worldTransformFont_, camera_);
	

	// 3Dオブジェクト描画処理後
	Model::PostDraw();

	
}
