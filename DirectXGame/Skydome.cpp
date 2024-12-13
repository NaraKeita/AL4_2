#include "Skydome.h"
#include <cassert>

void Skydome::Initialize(Model* model, Camera* viewProjection) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
}

void Skydome::Update() { worldTransform_.UpdateMatrix(); }

void Skydome::Draw() { 
	model_->Draw(worldTransform_, *viewProjection_); }
