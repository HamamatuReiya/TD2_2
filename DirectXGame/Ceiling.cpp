#include "Ceiling.h"

void Ceiling::Initialize(Model* model) {
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {40.0f, 3.0f, 36.0f};
}

void Ceiling::Update() {
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

void Ceiling::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);
}
