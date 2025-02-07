#include "RailCamera.h"
#include "imgui.h"

void RailCamera::Initialize(KamataEngine::Vector3 position, KamataEngine::Camera* camera, float radian) {
	// 引数でワールド座標を受け取ってワールドトランスフォームに設定
	worldTransform_.translation_ = position;
	// 引数で回転角を受け取ってワールドトランスフォームに設定
	worldTransform_.rotation_ = KamataEngine::Vector3(0.0f, radian, 0.0f);
	// カメラの初期化
	camera_ = camera;
}

void RailCamera::Update() {
	// ワールドトランスフォームの座標の数値を加算したりする(移動)
	worldTransform_.translation_.x += 0.1f;
	// ワールドトランスフォームの角度の数値を加算したりする(回転)
	worldTransform_.rotation_.y += 0.01f;
	// ワールドトランスフォームのワールド行列再計算
	worldTransform_.NoTransferUpdateMatrix();

	// カメラオブジェクトのワールド行列からビュー行列を計算する
	camera_->matView = Inverse(worldTransform_.matWorld_);

	ImGui::Begin("Camera");
	// スライダーでカメラのtranslationを表示
	ImGui::SliderFloat3("Translation", &worldTransform_.translation_.x, -100.0f, 100.0f);
	// スライダーでカメラのrotationを表示
	ImGui::SliderFloat3("Rotation", &worldTransform_.rotation_.x, -DirectX::XM_PI, DirectX::XM_PI);
	ImGui::End();
}
//
//const KamataEngine::WorldTransform& RailCamera::GetWorldTransform() const { return worldTransform_; }
//
//const KamataEngine::Camera* RailCamera::GetCamera() { return camera_; }
