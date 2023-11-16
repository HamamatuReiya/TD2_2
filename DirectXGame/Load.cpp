#include "Load.h"

void Load::Initialize(
    Model* model, Model* model1, Model* model2, Model* model3, Model* model4, Model* model5) {
	model_ = model;
	model1_ = model1;
	model2_ = model2;
	model3_ = model3;
	model4_ = model4;
	model5_ = model5;
	for (int i = 0; i < 6; i++) {
		worldTransform_[i].Initialize();
		worldTransform_[i].scale_ = {1.0f, 1.0f, 1.0f};
		worldTransform_[i].rotation_ = {0.0f, 0.0f, 0.0f};
	}
	worldTransform_[0].translation_ = {-4.0f, 0.0f, 20.0f};
	worldTransform_[1].translation_ = {-4.0f, 0.0f, 56.0f};
	worldTransform_[2].translation_ = {18.0f, 0.0f, 76.0f};
	worldTransform_[3].translation_ = {12.0f, 0.0f, 40.0f};
	worldTransform_[4].translation_ = {48.0f, 0.0f, 36.0f};
	worldTransform_[5].translation_ = {70.0f, 0.0f, 46.0f};
}

void Load::Update() {
	for (int i = 0; i < 6; i++) {
		// 行列の更新
		worldTransform_[i].UpdateMatrix();
	}
}

void Load::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_[0], viewProjection);
	model1_->Draw(worldTransform_[1], viewProjection);
	model2_->Draw(worldTransform_[2], viewProjection);
	model3_->Draw(worldTransform_[3], viewProjection);
	model4_->Draw(worldTransform_[4], viewProjection);
	model5_->Draw(worldTransform_[5], viewProjection);
}
