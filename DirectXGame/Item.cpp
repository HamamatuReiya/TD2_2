#include "Item.h"

void Item::Initialize(Model* keyupModel, Model* keydownModel, Model* keymoldModel) {
	//鍵モデル
	keyupModel_ = keyupModel;
	keydownModel_ = keydownModel;
	keymoldModel_ = keymoldModel;
	for (int i = 0; i < 3; i++) {
		worldTransform_[i].Initialize();
		worldTransform_[i].scale_ = {1.0f, 1.0f, 1.0f};
		worldTransform_[i].rotation_ = {0.0f, -45.0f, 0.0f};
		worldTransform_[i].translation_ = {0.0f, -1.0f, 0.0f};
	}
}

void Item::Update() {
	//ランダム
	//1～3を鍵分とアイテム個別で用意
	Keynumber = static_cast<float>(rand() % 3 + 1);

	if (Keynumber == 1) {
		worldTransform_[0].translation_ = {-2.0f, -1.0f, 0.0f};
		worldTransform_[1].translation_ = {0.0f, -1.0f, 0.0f};
		worldTransform_[2].translation_ = {2.0f, -1.0f, 0.0f};
	}
	if (Keynumber == 2) {
		worldTransform_[0].translation_ = {-4.0f, -1.0f, 0.0f};
		worldTransform_[1].translation_ = {0.0f, -1.0f, 0.0f};
		worldTransform_[2].translation_ = {4.0f, -1.0f, 0.0f};
	}
	if (Keynumber == 3) {
		worldTransform_[0].translation_ = {-6.0f, -1.0f, 0.0f};
		worldTransform_[1].translation_ = {0.0f, -1.0f, 0.0f};
		worldTransform_[2].translation_ = {6.0f, -1.0f, 0.0f};
	}
	for (int i = 0; i < 3; i++) {
		// 行列の更新
		worldTransform_[i].UpdateMatrix();
	}
}

void Item::Draw(ViewProjection& viewProjection) {
	for (int i = 0; i < 3; i++) {
		keyupModel_->Draw(worldTransform_[0], viewProjection);
		keydownModel_->Draw(worldTransform_[1], viewProjection);
		keymoldModel_->Draw(worldTransform_[2], viewProjection);
	}
}


