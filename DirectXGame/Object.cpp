#include "Object.h"

void Object::Initialize(Model* model) {
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
}

void Object::Update() {
	// �s��̍X�V
	worldTransform_.UpdateMatrix();
}

void Object::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}
