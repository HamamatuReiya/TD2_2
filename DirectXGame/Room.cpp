#include "Room.h"

void Room::Initialize(
    Model* model, Model* model1, Model* model2, Model* model3, Model* model4, Model* model5,
    Model* model6) {
	model_ = model;
	model1_ = model1;
	model2_ = model2;
	model3_ = model3;
	model4_ = model4;
	model5_ = model5;
	model6_ = model6;
	for (int i = 0; i < 7; i++) {
		worldTransform_[i].Initialize();
		worldTransform_[i].scale_ = {1.0f, 1.0f, 1.0f};
		worldTransform_[i].rotation_ = {0.0f, 0.0f, 0.0f};
	}
	worldTransform_[0].translation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_[1].translation_ = {-2.0f, 0.0f, 40.0f};
	worldTransform_[2].translation_ = {4.0f, 0.0f, 72.0f};
	worldTransform_[3].translation_ = {40.0f, 0.0f, 76.0f};
	worldTransform_[4].translation_ = {28.0f, 0.0f, 42.0f};
	worldTransform_[5].translation_ = {74.0f, 0.0f, -8.0f};
	worldTransform_[6].translation_ = {66.0f, 0.0f, 40.0f};
}

void Room::Update() {
	for (int i = 0; i < 7; i++) {
		// 行列の更新
		worldTransform_[i].UpdateMatrix();
	}
}

void Room::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_[0], viewProjection);
	model1_->Draw(worldTransform_[1], viewProjection);
	model2_->Draw(worldTransform_[2], viewProjection);
	model3_->Draw(worldTransform_[3], viewProjection);
	model4_->Draw(worldTransform_[4], viewProjection);
	model5_->Draw(worldTransform_[5], viewProjection);
	model6_->Draw(worldTransform_[6], viewProjection);
}
