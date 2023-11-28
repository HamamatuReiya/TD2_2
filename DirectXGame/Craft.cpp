#include "Craft.h"

void Craft::Initialize(Model* model) {
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {59.0f, 0.0f, 49.0f};
}

void Craft::Update() {
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

void Craft::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection);

}
Vector3 Craft::GetCraftWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Craft::OnCraftCollision() {}
