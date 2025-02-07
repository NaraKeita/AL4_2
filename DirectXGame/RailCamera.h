#pragma once
#include "Affin.h"
#include <3d/Camera.h>
#include <DirectXMath.h>
#include <KamataEngine.h>
#include <imgui.h>

class RailCamera {
public:
	void Initialize(KamataEngine::Vector3 position, KamataEngine::Camera* camera, float radian);
	void Update();
	const KamataEngine::WorldTransform& GetWorldTransform() const;

	const KamataEngine::Camera* GetCamera();

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera* camera_ = nullptr;
	
};
